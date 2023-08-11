#ifndef LIST_H
#define LIST_H
#include "new_types.h"
info_cmd *add_node_end(info_cmd **head, const char *str);
void free_list(info_cmd *head);
#endif
