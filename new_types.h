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

typedef struct alias_t  Alias;
/**
 * struct alias_t - structure contains shorcuts of command
 * @name:  name of alias
 * @value: real command with its arguments
 * @next:  next node adress
 *
 * Description: this will be used in linked list , each node(name, value)
 */
struct alias_t
{
char *name;
char *value;
Alias *next;
};

#endif
