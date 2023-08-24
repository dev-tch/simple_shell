#include "new_types.h"
#include "list.h"
#include "common.h"
#include <stddef.h>
#include "strings.h"
#include "helper_functions.h"

/**
* proc_alias - handle alias in main_shell
* @h:  list contains command
* @al: list contains alias
* Return: (void)
*/
void proc_alias(LinkedList **h, LinkedList *al)
{
	char *new_value = (*h)->arg;
	char *value;
	int ret_del = 0;
	int prefix_len;

	if (is_builtin(new_value))
		return;

	while (al != NULL)
	{
		value = (al->arg);
		prefix_len = al->idx_sep;

		if (get_beginsWith(value, new_value) && _strlen(new_value) == prefix_len)
		{
			new_value = (value + prefix_len + 1);
		}
		al = al->next;
	}

	if (_strcmp(new_value, (*h)->arg) != 0)
	{
		ret_del =  delete_first_node(h);
		if (ret_del == -1)
		return;
		add_node_first(h, new_value);
	}
}
