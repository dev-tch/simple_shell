#ifndef LIST_H
#define LIST_H
#include "new_types.h"
#include "helper_functions.h"
LinkedList *add_node_end(LinkedList **head, const char *str);
void free_list(LinkedList *head);
int list_len(const LinkedList *h);
char **list_to_array(LinkedList *h);
int delete_first_node(LinkedList **head);
LinkedList *add_node_first(LinkedList **head, const char *str);
void conv_env_to_list(LinkedList **list_env, char **env);
void  print_list(char *program, LinkedList *h);
char *get_node_by_prefix(char *prefix, LinkedList *h);
#endif
