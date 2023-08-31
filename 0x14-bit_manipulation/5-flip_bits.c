#include "main.h"

/**
 * flip_bits - returns the number of bits you would need to flip to
 * get from one number to another
 *
 * @n: initial number
 * @m: required number
 *
 * Return: number of bits that needs to be fliped
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	unsigned long int diff = n ^ m, mask = 1;
	unsigned int i = 0, count = 0;

	for (i = 0; i < sizeof(unsigned long int) * 8; i++)
	{
		if (mask == (diff & mask))
			count++;
		mask <<= 1;
	}

	return (count);
}
