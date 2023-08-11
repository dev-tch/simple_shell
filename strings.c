#include <stddef.h>
#include <stdlib.h>
/* new module for string functions*/

/**
* _strlen -length of string
* @str: string
* Return:length of string
*/
int _strlen(char *str)
{

	if (*str == '\0')
		return (0);
	return (1 + _strlen(str + 1));
}

/**
 * _strcat - concatenates two strings
 * @dest: input value
 * @src: input value
 *
 * Return: void
 */
char *_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - compare string values
 * @s1: input value
 * @s2: input value
 *
 * Return: s1[i] - s2[i]
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (0);
}

/**
 * char *_strcpy - a function that copies the string pointed to by src
 * @dest: copy to
 * @src: copy from
 * Return: string
 */
char *_strcpy(char *dest, char *src)
{
	int l = 0;
	int x = 0;

	while (*(src + l) != '\0')
	{
		l++;
	}
	for ( ; x < l ; x++)
	{
		dest[x] = src[x];
	}
	dest[l] = '\0';
	return (dest);
}

/**
*_strdup - new pointer to copied string
*@str: string
*Return: pointer to string
*/
char *_strdup(char *str)
{
	char *cpy = NULL;
	char *bkp = str;
	int len = 0, i;

	if (str == NULL)
		return (NULL);
	/*get the length*/
	while (*str)
	{
		len++;
		str++;
		}
	/* memory allocation*/
	cpy = (char *) malloc((len + 1) * sizeof(char));
	if (cpy == NULL)
		return (NULL);
	for (i = 0 ; i < len ; i++)
	{
		cpy[i] = bkp[i];
	}
	return (cpy);
}

