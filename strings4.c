#include <stddef.h>
#include <stdlib.h>
/**
* get_nb_digits - calculate number of digites of number
* @n: number
* Return: int
*/
int get_nb_digits(int n)
{
	n = n / 10;
	if (n == 0)
		return (1);
	return (1 + get_nb_digits(n));
}

/**
* conv_nb_to_str - save number in pointer
* @n: number
* Return: pointer to char
*/
/*function to full number in pointer  of chars*/
char *conv_nb_to_str(int n)
{
	int size, rem;
	int idx = 0;
	char *ptr;
	int  sign = 0;

	sign = (n < 0) ?  -1 : 1;

	size = get_nb_digits(n);
	/*one fo sign , one for '\0' and rest for number*/
	ptr = (char *) malloc(1 +  1  +  size);

	if (ptr == NULL)
	{
		return (NULL);
	}
	if (sign == 1)
		ptr[0]  = '+';
	else
		ptr[0] = '-';

	ptr[size + 1] = '\0';

	idx = size;
	while (idx  > 0)
	{
		rem = n % 10;
		n = n / 10;
		ptr[idx] = (rem * sign) + '0';
		idx--;
	}

	if (*ptr == '+')
		ptr++;
	return (ptr);
}
