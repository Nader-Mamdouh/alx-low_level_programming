#include "main.h"

/**
 * binary_to_uint - converts a binary number to an unsigned int
 *
 * @b: pointer to a string of 0 and 1 chars
 *
 * Return: converted number
 */
unsigned int binary_to_uint(const char *b)
{
	unsigned int n = 0, i = 0;

	if (b == NULL)
		return (0);

	for (i = 0; b[i] != '\0'; i++)
	{
		if (b[i] != '0' && b[i] != '1')
			return (0);

		n <<= 1;
		if (b[i] == '1')
			n += 1;
	}

	return (n);
}
