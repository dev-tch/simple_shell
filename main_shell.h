#ifndef MAIN_SHELL_H
#define MAIN_SHELL_H
/*bloc for includes*/
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "new_types.h"
#include <stdio.h>
/*here we define the prototypes of our functions */
int display_prompt(char *str, int size);
int lunch_shell_execution(char *program, info_cmd *h, char **env);
int clear_eof(FILE *stream, size_t len);
int handle_CTRD(size_t *n,  char **user_input);
#endif

