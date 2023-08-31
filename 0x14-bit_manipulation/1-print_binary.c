#include "main.h"

/**
 * print_binary - prints the binary representation of a number
 *
 * @n: number to print
 *
 * Return: void
 */
void print_binary(unsigned long int n)
{
	unsigned long int masked;
	int i, flag = 0;

	for (i = sizeof(unsigned long int) * 8 - 1; i >= 0; i--)
	{
		masked = n >> i;

		if (masked & 1)
		{
			flag = 1;
			_putchar('1');
		}
		else if (flag == 1)
			_putchar('0');
	}

	if (flag == 0)
		_putchar('0');
}
