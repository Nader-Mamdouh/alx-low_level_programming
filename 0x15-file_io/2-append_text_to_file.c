#include "main.h"

/**
 * append_text_to_file - appends text at the end of a file.
 *
 * @filename: the name of the file
 * @text_content: a NULL terminated string to add at the end of the file
 *
 * Return: 1 on success and -1 on failure
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int o, w, n = 0;

	if (filename == NULL)
		return (-1);

	while (text_content != NULL && text_content[n] != '\0')
		n++;

	o = open(filename, O_WRONLY | O_APPEND);
	w = write(o, text_content, n);

	if (o == -1 || w == -1 || w != n)
		return (-1);

	close(o);
	return (1);
}
