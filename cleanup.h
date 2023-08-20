#ifndef CLEANUP_H
#define CLEANUP_H
#include "new_types.h"
#include <stddef.h>
void cleanupArray(int len_args, char ***args);
void cleanupInput(char **input, size_t *n);
void cleanupList(info_cmd **head);
#endif
