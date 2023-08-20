#include "new_types.h"
#include <stddef.h>
#include <stdlib.h>
#include "list.h"
#include <stdio.h>
/**
* delete_first_node - delete node at index 0
* @head: pointer to the pointer of node
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
	free(temp);
	return (1);
}
/**
* conv_env_to_list -  convert array env to list
* @list_env: pointer to pointer of head list
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

/**
* print_list - print the nodes of list
* @h: pointer to first elment in list (HEAD)
* Return: number of elmements in list
*/
int print_list(LinkedList *h)
{
	int nb_nodes = 0;

	while (h != NULL)
	{
		nb_nodes++;
		if (h->arg == NULL)
		{
			printf("[0] (nil)\n");
		}
		else
		{
			printf("[%d] [%d] %s\n", h->len, h->idx_sep, h->arg);
		}
		h = h->next;
	} /*while loop*/

	return (nb_nodes);
}

