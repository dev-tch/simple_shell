#include <stddef.h>
/**
* is_space - check character space
* @c: character
* Return: (1 or 0)
*/
int is_space(char c)
{
return (c == ' ' || c == '\t' || c == '\r');
}
/**
* is_empty - check empty string
* @str: sring
* Return: (1 or 0)
*/
int is_empty(char  *str)
{
	if (str == NULL)
	{
	return (1);
	}

	while (*str != '\0')
	{
		if (!is_space(*str))
		return (0);
		str++;
	}

	return (1);
}
