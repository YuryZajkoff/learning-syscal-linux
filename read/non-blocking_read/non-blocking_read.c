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
    char buffer[BUFFER_SIZE + 1];
    
    if (argc < 2)
    {
        fprintf(stderr, "Too few arguments\n");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY, O_NONBLOCK);
    if (fd < 0)
    {
        fprintf(stderr, "Cannot open file\n");
        exit(1);
    }

start:
    ret = read(fd, buffer, len);
    if (ret == -1)
    {
        if (errno == EINTR)
            goto start; /* here's the bad luck */
        if (errno == EAGAIN)
        {
            /* repeat the call later */
        }
        else
        {
            perror("read");
        }
    }

    close(fd);
    printf("\n");

    fprintf(stderr, "Press <Enter> to exit...");
    getchar();

    exit(0);
}