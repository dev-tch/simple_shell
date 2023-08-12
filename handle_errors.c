#include "strings.h" /*required toinclude string functions*/
#include  <stdlib.h> /*required toinclude the function malloc*/
#include  <stdio.h>  /*required to include the function perror*/
#include  <errno.h>  /*reuired toinclude globalvariable errno*/
#include "errors.h"
/**
* get_error_value - return the value error
* @code: error code
* Return: value of error
*/
char *get_error_value(unsigned int  code)
{
unsigned int i = 0;
static char *err[14];
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
err[16] = ": Unknown Error";
for (i = 0 ; i < 17 ; i++)
{
if (i == code)
return (err[i]);
}
return (": Unknown Error");
}
/**
* print_error - display error message on standart error
* @program: name of shell program
* @err_code: error code
* @type_error: (standart error or new defined error)
* Return: void
*/
void print_error(char *program, int err_code, int type_error)
{
int err_num = 0;
char *dest;
char *err_value;


err_num = errno;
/*test the error exist in errno*/
if (err_num != 0 && type_error == STD_ERROR)
{
	perror(program);
	errno = 0;
}
else
{
	/*new defined error*/
	errno = 0;
	err_value = get_error_value(err_code);
	dest = (char *) malloc((_strlen(program) + _strlen(err_value) - 1));
	_strcat(dest, program);
	_strcat(dest, err_value);
	perror(dest);
	free(dest);
}
}
