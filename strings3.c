#include <stddef.h>
/**
* get_index_sep - get the index of seperator that exist in string
* @sep: seperator
* @str: String
* Return: index
**/
int get_index_sep(char *str, char sep)
{
	int i = 0;
	int index_sep = 0;

	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == sep)
		{
			index_sep = i;
			break;
		}
		i++;
	}
	return (index_sep);
}

/**
 * _strncpy - copy n elments from string src to dest
 * @dest: copy to
 * @src: copy from
 * @n: max number of copied characters(exclusive)
 * Return: the copied string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i = 0;

	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
