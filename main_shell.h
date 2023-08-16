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
int lunch_shell_execution(char *prg, int len_args, char **args, char **env);
int clear_eof(FILE *stream, size_t len);
int handle_CTRD(size_t *n,  char **user_input);
int shell_exit(char *prg, int len_args, char **cmd_args, char **env);
int lunch_builtin(char *prog, int len_args, char **cmd_args, char **env);
int print_env(char *prg, int len_args, char **cmd_args, char **env);
#endif

