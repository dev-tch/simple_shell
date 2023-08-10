
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

