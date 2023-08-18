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
int is_builtin(char *name_cmd);
int print_env(char *prg, int len_args, char **cmd_args, char **env);
int get_beginsWith(char *src, char *pattern);
char *get_path_value(char **env);
int convert_path_to_list(char *prg, char **env,  info_cmd **head_path);
char *lookup_in_path(char *name_cmd, info_cmd *head_path);
#endif

