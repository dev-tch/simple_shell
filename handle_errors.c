#include "strings.h" /*required toinclude string functions*/
#include  <stdlib.h> /*required toinclude the function malloc*/
#include  <stdio.h>  /*required to include the function perror*/
#include  <errno.h>  /*reuired toinclude globalvariable errno*/
#include "errors.h"

/**
* get_error_value - return the value error
* @code: the error code
* Return: value of error
*/
char *get_error_value(unsigned int  code)
{
unsigned int i = 0;
static char *err[21];

/*define errors*/
err[0]  = ": SUCCESS";
err[1]  = ": Operation not permitted";
err[2]  = ": No such file or directory";
err[3]  = ": No such process";
err[4]  = ": Interrupted system call";
err[5]  = ": I/O error";
err[6]  = ": No such device or address";
err[7]  = ": The argument list is too long";
err[8]  = ": Exec format error";
err[9]  = ": Bad file number";
err[10] = ": No child processes";
err[11] = ": Try again";
err[12] = ": Out of memory";
err[13] = ": Permission denied";
err[14] = ": Malloc Failed";
err[15] = ": Echec reading Line";
err[16] = ": 1: exit: Illegal number";
err[17] = ": ILLigal number of arguments";
err[18] = ": Environnement variable Not found";
err[19] = ": alias";
err[20] = ": Unknown Error";

for (i = 0 ; i < 21 ; i++)
{
	if (i == code)
		return (err[i]);
}
return (": Unknown Error");
}
/**
* print_error - display error message on standart error
* @program: the name of shell program
* @err_code: error code
* @type_error: (standart error or new defined error)
* Return: void
*/
void print_error(char *program, int err_code, int type_error)
{
	/*variables declartion*/
	int err_num = 0;
	char *dest  = NULL;
	char *err_value = NULL;
	int is_ok = 0;
	int fd = 2;
	char *new_line  = "\n";
	int size = 0;

	err_num = errno;
	/*test the error exist in errno*/
	if (err_num != 0 && type_error == STD_ERROR && program != NULL)
	{
		perror(program);
		/*errno = 0;*/
		return;
	}

	err_value = get_error_value(err_code);
	is_ok = err_value != NULL && program != NULL;

	if (type_error == NEW_ERROR  && is_ok)
	{
		/*errno = 0;*/
		/*new defined error*/
		size = _strlen(program) + _strlen(err_value) + 1 + 1;
		dest = (char *) malloc(size);
		if (dest != NULL)
		{
			_strcpy(dest, program);
			_strcat(dest, err_value);
			_strcat(dest, new_line);
			write(fd, dest, size);
			free(dest);
			dest = NULL;
		}
	}
}

/**
* print_err_plus - display error message on standart error
* @program: name of shell program
* @err_code: the error code
* @type_error: (standart error or new defined error)
* @cmd_arg: name of command to excute
* Return: void
*/
void print_err_plus(char *program, int err_code, int type_error, char *cmd_arg)
{
	int err_num = 0;
	char *dest  = NULL;
	char *err_value = NULL;
	int size = 0, size2 = 0;
	char *empty_err = ": ";
	char *new_line  = "\n";
	int fd = 2; /*file descriptor for stderr*/
	int is_ok = 0;

	err_num = errno;
	/*test the error exist in errno*/
	if (err_num != 0 && type_error == STD_ERROR && program != NULL)
	{
		perror(program);
		/*errno = 0;*/
		return;
	}
	err_value = get_error_value(err_code);
	is_ok = err_value != NULL && program != NULL && cmd_arg != NULL;

	if (type_error == NEW_ERROR && is_ok)
	{
		/*errno = 0;*/
		/*a new defined error*/
		size = _strlen(program)  + _strlen(err_value) + _strlen(cmd_arg);
		size2 = _strlen(empty_err) + _strlen(new_line);
		dest = (char *) malloc((size + size2 + 1));
		if (dest != NULL)
		{
			/*_strcat(dest, program);*/
			_strcpy(dest, program);
			_strcat(dest, err_value);
			_strcat(dest, empty_err);
			_strcat(dest, cmd_arg);
			_strcat(dest, new_line);
			write(fd, dest, (size + size2));
			free(dest);
			dest = NULL;
		}
	}
}
/**
* print_err_127 - new error - command not in path
* @program: initial shell program
* @arg: name of comand
* Return: void
*/
void print_err_127(char *program, char *arg)
{
	char *sep = ": 1: ";
	char *end = ": not found\n";
	char *dest      = NULL;
	int size        = 0;
	int fd = 2; /*file descriptor for stderr*/

	size = _strlen(program)  + _strlen(sep) + _strlen(arg) + _strlen(end);
	dest = (char *) malloc(size + 1);

	if (dest != NULL)
	{
		/*_strcat(dest, program);*/
		_strcpy(dest, program);
		_strcat(dest, sep);
		_strcat(dest, arg);
		_strcat(dest, end);
		write(fd, dest, (size));
		free(dest);
		dest = NULL;
	}
}
