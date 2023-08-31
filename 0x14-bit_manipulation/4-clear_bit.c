#include "main.h"

/**
 * clear_bit - clears the value of a bit at a given index
 *
 * @n: number
 * @index: index of bit to return
 *
 * Return: int - 1 on success, -1 otherwise
 */
int clear_bit(unsigned long int *n, unsigned int index)
{
	unsigned long int mask = 1;

	if (index > sizeof(unsigned long int) * 8 - 1)
		return (-1);

	mask <<= index;

	*n = *n & (~mask);

	return (1);
}
