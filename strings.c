#include <stddef.h>
#include <stdlib.h>

/* new module for string functions*/

/**
* _strlen - length of string
* @str: string
*
* Return:length of string
*/
int _strlen(char *str)
{
	int len = 0;
	int i = 0;

	if (str == NULL)
		return (0);

	while (str[i] != '\0')
	{
		len++;
		i++;
	}

	return (len);
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
	/*variables declarations */
	/*int x = 0;*/
	/*int y = 0;*/
	char *tmp = NULL;

	/*Main _strcat*/
	if (dest == NULL || src == NULL)
		return (NULL);

	tmp = dest + _strlen(dest);

	while (src != NULL && *src != '\0')
	{
		if (tmp != NULL)
		{
			*tmp = *src;
			tmp++;
			src++;
		}
		else
		{
			return (NULL);
		}
	}

	if (tmp != NULL)
	{
		*tmp = '\0';
	}
	else
		return (NULL);

	return (dest);
}

/**
 * _strcpy - a function that copies the string pointed to by src
 * @dest: copy to
 * @src: copy from
 * Return: the copied string
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
*Return: a pointer to string
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
	/*add character terminating to string*/
	cpy[i] = '\0';
	return (cpy);
}

/**
 * _strcmp - compare two strings
 *@s1: the first string
 *@s2: the second string
 * Return: int
 */
int _strcmp(char *s1, char *s2)
{
int i = 0;
/*Main */
while (s1[i] != '\0' || s2[i] != '\0')
{
if (s1[i] != s2[i])
return (s1[i] - s2[i]);
i++;
}
return (0);
}

