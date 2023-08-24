#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include "list.h"
int is_builtin(char *name_cmd);
int save_commands(LinkedList **cmds, char *input);
void printMsg(LinkedList *alia);
char *nodeBeginsWithVar(char *prefix, LinkedList *h);
void print_alia_reverse(LinkedList *h);
#endif
