#ifndef NEW_TYPES_H
#define NEW_TYPES_H

typedef struct listcmd_t  info_cmd;
/**
 * struct listcmd_t - list cmd_name and arguments
 * @arg: command argument
 * @len: lenght of an argument
 * @next: next node adress
 *
 * Description: head of list = command name; rest = arguments of command
 */
struct listcmd_t
{
char *arg;
int len;
info_cmd *next;
};
#endif
