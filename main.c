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

if (argc != 3)
    {
        fprintf (stderr,"CsP slider - Create a sliding window of text from an input list\n");
        fprintf (stderr,"usage: %s min max\n",argv[0]);
        return -1;
    }

    char line_buff[BUFLEN];
    char * write_buffer = NULL;
    char * p;
    size_t line_len  = 0;
    size_t retBuffer = 0;
    int min = atoi(argv[1]);
    int max = atoi(argv[2]);

    if (min > max)
    {
        fprintf(stderr,"Error, min cannot be smaller than max\n");
        return -1;
    }

    write_buffer = (char *) malloc(BUFLEN + 1);
    if (!write_buffer)
    {
        fprintf(stderr, "Failed to allocate write_buffer\n");
        return -1;
    }

    while (fgets(line_buff, sizeof(line_buff), stdin) != NULL)
    {
        p = line_buff + strlen(line_buff) - 1;
        if (*p == '\n') *p = '\0';
        if ((p != line_buff) && (*--p == '\r')) *p = '\0';

        line_len = strlen(line_buff);

        if (min > line_len)
            continue;

        size_t pos = 0;
        for (pos = 0; pos<line_len; pos++)
        {
            for(size_t start = min; start <= max; start ++)
            {
                if (pos + start  > line_len)
                    break;
                memcpy(write_buffer+retBuffer,line_buff+pos,start);
                write_buffer[retBuffer+start] = '\n';
                retBuffer = retBuffer+start+1;

                if (retBuffer > 2000)
                {
                    fwrite(write_buffer,1,retBuffer,stdout);
                    retBuffer = 0;
                }
            }
        }

        if (retBuffer != 0)
        {
            fwrite(write_buffer,1,retBuffer,stdout);
            fflush(stdout);
            retBuffer = 0;
        }
    }
}
