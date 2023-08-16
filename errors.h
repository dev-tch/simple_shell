#ifndef ERRORS_H
#define ERRORS_H
#include <errno.h>
#define STD_ERROR  555
#define NEW_ERROR  666
#define MALLOC_ERROR 14
#define GETLINE_ERROR 15
#define EXIT_FAIL     1
#define EXIT_DONE     0
#define NOT_BUILT_IN 3
#define ILLIGAL_EXIT_NUMBER 16
#include <stdlib.h>
#include <unistd.h>
char *get_error_value(unsigned int  err_code);
void print_error(char *program, int err_code, int type_error);
void print_err_plus(char *prog, int err_code, int type_error, char *cmd_arg);
#endif
