#include "main_shell.h"
#include <errno.h>
#include "strings.h"
#include <string.h>
#include <stdio.h>
/**
* clear_eof - clear EOF from stdin
* @stream: stdin stream File
* @len: lenght of command enterd to stdin
* Return: void
*/
int  clear_eof(FILE *stream, size_t len)
{
	char buf_tst_eof[1024];
	int fd_stdin = 0, rd = 0;

	rd = read(fd_stdin, buf_tst_eof, len);
	if (rd == 0)
	{
		((stream)->_flags &= ~(_IO_ERR_SEEN | _IO_EOF_SEEN));
		return (1);
	}
	return (0);
}
/**
* handle_CTRD - handle key ctr+d in shell
* @n: the adress of the variable that holds the input buffer
* @user_input: the typed string in shell
* Return: (-1:  break the loop)(1: continue the loop)(2: other task to do)
*/
int handle_CTRD(size_t *n,  char **user_input)
{
	size_t  len;

	len = _strlen(*user_input);
	if (errno == 0 && (*user_input)[len - 1] != '\n')
	{
		if (!is_empty(*user_input))
		{
			if (clear_eof(stdin, len))
				return (1);
			else
				return (-1);
		}
		else
		{
			free(*user_input);
			*n = 0;
			return (-1);
		}
	}
	return (2); /*continue excution of code above*/
}
