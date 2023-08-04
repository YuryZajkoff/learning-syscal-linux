#include <fcntl.h>	   /* open() and O_XXX flags */
#include <sys/stat.h>  /* S_IXXX flags */
#include <sys/types.h> /* mode_t */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /* read(), write(), close() */
#include <string.h>

#define BUFFER_SIZE 64

/* 
	The first argument is to write the name of the file 
	that we want to create and write data there
*/
int main(int argc, char **argv)
{
	int fd;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP;
	int flags = O_WRONLY | O_TRUNC | O_CREAT;
	const char *buf = "My ship is solid!";
	ssize_t ret;
	size_t len;

	if (argc < 2)
	{
		fprintf(stderr, "Too few arguments\n");
		exit(1);
	}

	fd = open(argv[1], flags, mode);
	if (fd < 0)
	{
		fprintf(stderr, "Cannot open file\n");
		exit(1);
	}

	len = strlen(buf);
	ret = write(fd, buf, len);
	if (ret == -1)
	{
		fprintf(stderr, "error, check errno\n");
		exit(1);
	}
	else if (ret != len)
	{
		fprintf(stderr, "an error is possible, but the value 'errno' is not set\n");
		exit(1);	
	}
	printf("write was successful\n");

	if (close(fd) < 0)
	{
		fprintf(stderr, "Cannot close\n");
		exit(1);
	}

	fprintf(stderr, "Press <Enter> to exit...");
	getchar();

	exit(0);
}