#ifndef CLEANUP_H
#define CLEANUP_H
#include "new_types.h"
#include <stddef.h>
void cleanup(char **user_input, info_cmd **head, int len_args, char ***args);
void cleanup1(char **user_input, info_cmd **head);
void cleanup2(int len_args, char ***args);
void cleanup3(char **input, size_t *n);
#endif
