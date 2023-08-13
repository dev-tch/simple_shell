#ifndef ERRORS_H
#define ERRORS_H
#include <errno.h>
#define STD_ERROR  555
#define NEW_ERROR  666
#define MALLOC_ERROR 14
#define GETLINE_ERROR 15
#define EXIT_FAIL     1
#define EXIT_DONE     0
char *get_error_value(unsigned int  err_code);
void print_error(char *program, int err_code, int type_error);
#endif
