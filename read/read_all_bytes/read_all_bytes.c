#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    int fd;
    ssize_t ret;
    size_t len = BUFFER_SIZE;

    char *buf_PTR;
    char buffer[BUFFER_SIZE + 1];
    buf_PTR = &buffer[0];

    if (argc < 2)
    {
        fprintf(stderr, "Too few arguments\n");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Cannot open file\n");
        exit(1);
    }

    while (len != 0 && (ret = read(fd, buf_PTR, len)) != 0)
    {
        if (ret == -1)
        {
            if (errno == EINTR)
            {
                continue;
            }
            perror("read");
            break;
        }

        len -= ret;
        buf_PTR += ret;
        printf("%s", buffer);
    }

    close(fd);
    printf("\n");

    fprintf(stderr, "Press <Enter> to exit...");
    getchar();

    exit(0);
}
