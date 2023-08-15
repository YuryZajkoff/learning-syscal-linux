/* Написание, компиляция и запуск программы для чтения из файла, используя вызовы open(), read(), close() */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 64

// блочное чтение из файла (по 64 байта)
int main(int argc, char **argv)
{
	int fd;
	ssize_t read_bytes;
	char buffer[BUFFER_SIZE + 1];
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

	while ((read_bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_bytes] = 0; /* Null-terminator for C-string */
		fputs(buffer, stdout);
	}

	if (read_bytes < 0)
	{
		close(fd);
		fprintf(stderr, "myread: Cannot read file\n");
		exit(1);
	}
	close(fd);
	printf("\n");
	
	fprintf(stderr, "Press <Enter> to exit...");
	getchar();

	exit(0);
}
