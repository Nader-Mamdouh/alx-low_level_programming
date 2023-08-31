#include "main.h"

/**
 * get_bit - returns the value of a bit at a given index
 *
 * @n: number
 * @index: index of bit to return
 *
 * Return: int - value of bit at index
 */
int get_bit(unsigned long int n, unsigned int index)
{
	unsigned long int mask = 1;

	if (index > sizeof(unsigned long int) * 8 - 1)
		return (-1);

	mask <<= index;

	return ((n & mask) ? 1 : 0);
}
