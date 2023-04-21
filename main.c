#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define BUFLEN (BUFSIZ * 1000)

int main(int argc, char *argv[])
{

#ifdef _WINDOWS
_setmode (_fileno (stdin), _O_BINARY);
#endif // _WINDOWS

    if (argc != 3) {
        fprintf(stderr, "CsP slider - Create a sliding window of text from an input list\n");
        fprintf(stderr, "usage: %s min max\n", argv[0]);
        return -1;
    }

    char line_buf[BUFLEN];
    char * write_buf = NULL;
    char * p;
    size_t line_len = 0;
    int min = atoi(argv[1]);
    int max = atoi(argv[2]);

    if (min > max) {
        fprintf(stderr, "Error, min cannot be smaller than max\n");
        return -1;
    }

    write_buf = (char *) malloc(BUFLEN + 1);
    if (!write_buf) {
        fprintf(stderr, "Failed to allocate write_buf\n");
        return -1;
    }

    while (fgets(line_buf, sizeof(line_buf), stdin) != NULL) {
        p = line_buf + strlen(line_buf) - 1;
        if (*p == '\n') *p = '\0';
        if ((p != line_buf) && (*--p == '\r')) *p = '\0';

        line_len = strlen(line_buf);
        if (min > line_len)
            continue;

        for (size_t pos = 0; pos < line_len; pos++) {
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
