#include "main.h"

/**
 * create_file - creates a file
 *
 * @filename: the name of the file to create
 * @text_content: NULL terminated string to write to the file
 *
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
	int o, w, n = 0;

	if (filename == NULL)
		return (-1);

	while (text_content != NULL && text_content[n] != '\0')
		n++;

	o = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	w = write(o, text_content, n);

	if (o == -1 || w == -1 || w != n)
		return (-1);

	close(o);

	return (1);
}
