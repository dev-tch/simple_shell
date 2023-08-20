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
