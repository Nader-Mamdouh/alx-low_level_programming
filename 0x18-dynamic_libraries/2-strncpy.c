#include "main.h"

/**
* _strncpy - copy n bytes from source string to destination string
*
* @dest: destination string
* @src: source string
* @n: bytes to copy
*
* Return: A pointer to the resulting string
*/
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0';

	return (dest);
}
