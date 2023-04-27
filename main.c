#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

#ifdef _WINDOWS
_setmode (_fileno (stdin), _O_BINARY);
#endif // _WINDOWS

    if (argc < 3 || argc > 5) {
        fprintf(stderr, "CsP slider - Create a sliding window of text from an input list\n");
        fprintf(stderr, "usage: %s min max [lower] [upper]\n", argv[0]);
        return -1;
    }

    size_t min = strtoul(argv[1], NULL, 10);
    size_t max = strtoul(argv[2], NULL, 10);

    if (min < 1) {
        fprintf(stderr, "Error, min cannot be smaller than 1\n");
        return -1;
    }

    if (min > max) {
        fprintf(stderr, "Error, max cannot be smaller than min\n");
        return -1;
    }

    size_t lower = 0;
    size_t upper = 0;
    int enforce = 0;
    if (argc > 3) {
        lower = strtoul(argv[3], NULL, 10);
        upper = strtoul(argv[4], NULL, 10);

        if (lower < 0) {
            fprintf(stderr, "Error, lower cannot be smaller than 0\n");
            return -1;
        }

        if (lower < upper) {
            enforce = 1;
        }


    }

    char line_buf[BUFSIZ];
    char write_buf[BUFSIZ + 1];
    char * p;
    size_t line_len = 0;

    while (fgets(line_buf, sizeof(line_buf), stdin) != NULL) {
        line_len = strlen(line_buf);

        if (line_len == 0) continue;
        if (min > line_len) continue;

        p = line_buf + line_len - 1;
        if (*p == '\n') {
            *p = '\0';
            line_len--;
        }

        if ((p != line_buf) && (*--p == '\r')) {
            *p = '\0';
            line_len--;
        }

        if (enforce == 0) upper = line_len;
        else if (line_len > upper) line_len = upper;

        for (size_t pos = lower; pos < line_len; pos++) {
            if ((line_len - pos) < min) break;
            memcpy(write_buf, line_buf + pos, line_len - pos);
            write_buf[line_len - pos] = '\0';

            size_t end = line_len - pos;
            if (end > max) {
                end = max;
            }

            for(size_t cur = end; cur >= min; cur--) {
                write_buf[cur] = '\0';
                puts(write_buf);
            }
        }
    }
}
