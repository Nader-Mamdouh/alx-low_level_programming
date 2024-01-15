/**
 * rand - a custom rand function to hack the lottery
 *
 * number: 9 8 10 24 75 9
 *
 * Return: random number
 */
int rand()
{
	static int i = 0;

	i++;
	if (i == 1)
		return (8); // 8 % 16 + 1 = 9 (6th number)
	else if (i == 2)
		return (8); // 8 % 75 + 1 = 9 (1st number)
	else if (i == 3)
		return (7); // 7 % 75 + 1 = 8 (2nd number)
	else if (i == 4)
		return (9); // 9 % 75 + 1 = 10(3rd number)
	else if (i == 5)
		return (23);
	else if (i == 6)
		return (74);

	return (0);
}
