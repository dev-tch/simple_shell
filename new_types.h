#ifndef NEW_TYPES_H
#define NEW_TYPES_H

typedef struct list_data_shell  LinkedList;
/**
 * struct list_data_shell - list to handle shell data : envs, cmds, alias ...
 * @arg: data of each node
 * @len: length of data
 * @idx_sep:  index of character  '=' in data (for case alias)
 * @next: next node adress
 *
 * Description: helper list to hold data for processing shell commands
 */
struct list_data_shell
{
char *arg;
int len;
int idx_sep;
LinkedList *next;
};
#endif
