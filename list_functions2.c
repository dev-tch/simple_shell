#include "new_types.h"
#include <stddef.h>
#include <stdlib.h>
#include "list.h"
#include "common.h"
#include "helper_functions.h"
#include "strings.h"
/**
* delete_first_node - delete node at index 0
* @head: a pointer to the pointer of node
* Return: 1(succeeded) , -1(failed)
*/
int delete_first_node(LinkedList **head)
{
	LinkedList  *temp;

	if (head == NULL)
		return (-1);
	if (*head == NULL)
		return (-1);
	temp = *head;
	*head = (*head)->next;
	free(temp->arg);  /*fix valgrind memory leaks */
	temp->arg = NULL;
	free(temp);
	return (1);
}
/**
* conv_env_to_list -  convert array env to list
* @list_env: a pointer to pointer of head list
* @env: double pointer contains environnements
* Return: void
*/
void conv_env_to_list(LinkedList **list_env, char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		add_node_end(list_env, env[i]);
		i++;
	}
}
