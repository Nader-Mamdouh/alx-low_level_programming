#include "main.h"
#include <stdio.h>

void copy_file(char *file_from, char *file_to);
void check(int value, char *filename, int fd_from, int fd_to, int error_code);

/**
 * main - entry point
 *
 * @argc: argument count
 * @argv: argument list
 *
 * Return: 0 on success, ERROR_CODE on failure
 */
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		dprintf(
			STDERR_FILENO,
			"Usage: cp file_from file_to\n"
		);
		exit(97);
	}

	copy_file(argv[1], argv[2]);

	return (0);
}

/**
 * copy_file - copy file_from content to file_to
 *
 * @file_from: filename of original file
 * @file_to: filename of new file
 *
 * Return: void
 */
void copy_file(char *file_from, char *file_to)
{
	int fd_from, fd_to, r = 1024, w, c1, c2;
	mode_t file_perm;
	char buf[1024];

	fd_from = open(file_from, O_RDONLY);
	check(fd_from, file_from, -1, -1, 98);

	file_perm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
	fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC, file_perm);
	check(fd_to, file_to, fd_from, fd_to, 99);

	while (r == 1024)
	{
		r = read(fd_from, buf, 1024);
		check(r, file_from, fd_from, fd_to, 98);

		w = write(fd_to, buf, r);
		check(w, file_to, fd_from, fd_to, 99);

		if (r != w)
			check(-1, file_to, fd_from, fd_to, 99);
	}

	c1 = close(fd_from);
	check(c1, file_from, fd_from, fd_to, 100);

	c2 = close(fd_to);
	check(c2, file_to, fd_from, fd_to, 100);
}

/**
 * check - checks for errors
 *
 * @value: flag
 * @filename: filename to print in error message
 * @fd_from: file descriptor of file_from
 * @fd_to: file descriptor of file_to
 * @error_code: error code
 *
 * Return: void
 */
void check(int value, char *filename, int fd_from, int fd_to, int error_code)
{
	if (value != -1)
		return;

	if (fd_from != -1)
		close(fd_from);

	if (fd_to != -1)
		close(fd_to);

	if (error_code == 98)
	{
		dprintf(
			STDERR_FILENO,
			"Error: Can't read from file %s\n",
			filename
		);
		exit(98);
	}
	else if (error_code == 99)
	{
		dprintf(
			STDERR_FILENO,
			"Error: Can't write to %s\n",
			filename
		);
		exit(99);
	}
	else if (error_code == 100)
	{
		dprintf(
			STDERR_FILENO,
			"Error: Can't close fd %s\n",
			filename
		);
		exit(100);
	}
}
