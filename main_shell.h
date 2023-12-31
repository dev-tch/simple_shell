#ifndef MAIN_SHELL_H
#define MAIN_SHELL_H
/*bloc for includes*/
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "strings.h"
#include <string.h>
#include "new_types.h"
#include <stdio.h>
/*here we define the prototypes of our functions */
int display_prompt(char *str, int size);
int lunch_shell_execution(char *prg, int len_args, char **args, char **env,
int *status_code);
/*int clear_eof(FILE *stream, size_t len);*/ /*test 11*/
int handle_CTRD(size_t *n,  char **user_input);
int shell_exit(char *prg, int la, char **arg, char **env,
LinkedList **env_t, LinkedList **alia_l);
int lunch_builtin(char *prg, int la, char **arg, char **env,
LinkedList **env_t, LinkedList **alia_l);
int is_builtin(char *name_cmd);
int print_env(char *prg, int la, char **arg, char **env,
LinkedList **env_t, LinkedList **alia_l);
int get_beginsWith(char *src, char *pattern);
char *get_path_value(char **env);
int convert_path_to_list(char *prg, char **env,  LinkedList **head_path);
char *lookup_in_path(char *name_cmd, LinkedList *head_path);
void proc_alias(LinkedList **h, LinkedList *al);
#endif

