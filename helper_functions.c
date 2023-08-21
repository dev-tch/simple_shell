#include "strings.h"
#include "errors.h"
/**************** methode to write message with new line */

/**
* printMsgWithNewLine - print msg with jump to new line
* @program: initial program that lunch shell
* @msg: message to print in stdout
* Return: void
*/
void printMsgWithNewLine(char *program, char *msg)
{
	int len_msg = 0, size = 0;
	char *new_line = "\n";
	char *dest = NULL;
	int fd = 1; /*stdout*/


	len_msg = _strlen(msg);
	size = len_msg + _strlen(new_line) + 1;
	dest = malloc(size);
	if (dest != NULL)
	{
		if (msg != NULL)
		{
			_strcpy(dest, msg);
			_strcat(dest, new_line);
		}
		else
		{
			free(dest);
			dest = NULL;
		}
		write(fd, dest, len_msg + 1);
		free(dest);
		dest = NULL;
	}
	else
	{
		print_error(program, MALLOC_ERROR, NEW_ERROR);
	}
}
/**
* print_error_alias - print error message if alias not found
* @program: initial shell program
* @input_data: name of alias that cause problem
* Return: void
*/
void print_error_alias(char *program, char *input_data)
{
	char *def_msg = ": not found";
	int  size = 0;
	char *dest = NULL;

	size =  _strlen(input_data) + _strlen(def_msg) +  1;
	dest = malloc(size);
	_strcpy(dest, input_data);
	_strcat(dest, def_msg);
	print_err_plus(program, ALIAS_NOT_FOUND, NEW_ERROR, dest);
	free(dest);
	dest = NULL;
}