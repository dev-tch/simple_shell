#include <stddef.h>
#include <string.h>
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
* @str: a string
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
 * _strchr - Entry point
 * @s: input
 * @c: input
 * Return: Always 0 (Success)
 */

char *_strchr(char *s, char c)
{
	int i = 0;

	for (; s[i] >= '\0'; i++)
	{
		if (s[i] == c)
			return (&s[i]);
	}
	return (0);
}

/**
 * split - split a string based on a separator
 * @str: input string
 * @separators: separator character
 *
 * Return: pointer to the first token, or NULL if no more tokens found
 */

char *split(char *str, char *separators)
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
		if (_strchr(separators, *token) != NULL)
		{
			*token = '\0';
			token++;
			return (result);
		}
		token++;
	}

	return (result);
}
/**
 * _atoi - converts string to integer
 *@s: a pointer to char
 * Return: int
 */

int _atoi(char *s)
{
int i;
int h, p;
h = 0;
p = -1;
for (i = 0; s[i] != '\0'; i++)
{
if (s[i] == '-')
p *= -1;
if (s[i] > 47 && s[i] < 58)
{
if (h < 0)
h = (h * 10) - (s[i] - '0');
else
h = (s[i] - '0') * -1;
if (s[i + 1] < 48 || s[i + 1] > 57)
break;
}
}
if (p < 0)
h *= -1;
return (h);
}

