#ifndef COMMON_H
#define COMMON_H
#include "list.h"
int var_exist(char *var_name, char *var_value, info_cmd **env_t);
int get_beginsWith(char *src, char *pattern);
int set_env(char *prg, int la, char  **arg, char **env, info_cmd **env_t);
int unset_env(char *prg, int la, char  **arg, char **env, info_cmd **env_t);
int print_env(char *prg, int la, char **arg, char **env, info_cmd **env_t);
#endif
