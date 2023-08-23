#include "main_shell.h"
#include <errno.h>
#include "strings.h"
#include <string.h>
#include <stdio.h>
#include "cleanup.h"

/*clear_eof deleted  - test 11*/
/**
* handle_CTRD - handle key ctr+d in shell
* @n: adress of the variable that holds the input buffer
* @input: the typed string in shell
* Return: (-1:  break the loop)(1: continue the loop)(2: other task to do)
*/
int handle_CTRD(size_t *n,  char **input)
{
	size_t  len = 0;
	int err_num = 0;

	err_num = errno;
	if (err_num == 0 && (input == NULL || *input == NULL))
	{
		return (-1);
	}
	else if (err_num == 0 && ((*input)[0] == '\0'))
	{
		cleanupInput(input, n);
		return (-1);
	}
	else
	{
		len = _strlen(*input);
		if (err_num == 0  && len >= 1 && (*input)[len - 1] != '\n')
		{
			if (!is_empty(*input))
			{
				/*return (1);*/
				return (-1);
			}
			else
			{
				cleanupInput(input, n);
				return (-1);
			}
		}
	}
	return (2); /*continue other instructions of read_command*/
}
