#ifndef CLEANUP_H
#define CLEANUP_H
#include "new_types.h"
void cleanup(char **user_input, info_cmd **head, int len_args, char ***args);
void cleanup1(char **user_input, info_cmd **head);
void cleanup2(int len_args, char ***args);
#endif
