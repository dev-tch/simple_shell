#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include "list.h"
void printMsgWithNewLine(char *program, char *msg);
void print_error_alias(char *program, char *input_data);
int save_commands(LinkedList **cmds, char *input);
#endif
