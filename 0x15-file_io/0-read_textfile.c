#include "main.h"

/**
 * read_textfile - reads a text file and prints it to the POSIX standard output
 *
 * @filename: string - filename
 * @letters: the number of letters it should read and print
 *
 * Return: the actual number of letters it could read and print
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd = open(filename, O_RDONLY);
	int n, w;
	char *buf = malloc(sizeof(char) * letters + 1);

	if (fd == -1 || filename == NULL || buf == NULL)
		return (0);

	n = read(fd, buf, letters);

	if (n == -1)
		return (0);

	w = write(STDOUT_FILENO, buf, n);

	if (w != n)
		return (0);

	free(buf);
	close(fd);

	return ((ssize_t)n);
}
