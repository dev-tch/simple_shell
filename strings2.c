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

/**
 * split - split a string based on a separator
 * @str: input string
 * @separator: separator character
 *
 * Return: pointer to the first token, NULL if no more tokens found
 */
char *split(char *str, char separator)
{
	static char *token;
	char *result;

	if (str != NULL)
	{
	token = str;
	}
	if (token == NULL || *token == '\0')
	{
	return (NULL);
	}

	result = token;
	while (*token != '\0')
	{
		if (*token == separator)
		{
			*token = '\0';
			token++;
			return (result);
		}
		token++;
	}

	return (result);
}
