#ifndef COMMON_H
#define COMMON_H
#include "list.h"
int var_exist(char *var_name, char *var_value, LinkedList **env_l);
int get_beginsWith(char *src, char *pattern);
int set_env(char *prg, int la, char  **arg, char **env, LinkedList **env_l,
LinkedList **alia_l);
int unset_env(char *prg, int la, char  **arg, char **env, LinkedList **env_l,
LinkedList **alia_l);
int print_env(char *prg, int la, char **arg, char **env, LinkedList **env_l,
LinkedList **alia_l);
int doAlias(char *prg, int la,  char **args, char **env, LinkedList **env_l,
LinkedList **alia_l);
#endif
