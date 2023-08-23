#include "new_types.h"
#include <stddef.h>
#include <stdlib.h>
#include "list.h"
#include <stdio.h>
#include "common.h"
#include "helper_functions.h"
#include "strings.h"
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
	free(temp->arg);  /*fix valgrind memory leaks */
	temp->arg = NULL;
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
* @program: initila shell program
* @h: pointer to first elment in list (HEAD)
* Return: number of elmements in list
*/
void print_list(char *program, LinkedList *h)
{
	while (h != NULL)
	{
		if (h->arg != NULL)
			printMsgWithNewLine(program, h->arg);
		h = h->next;
	} /*while loop*/
}
/**
* get_node_by_prefix - search if info begins with prefix in list
* @prefix: pattern that h->arg begins
* @h: linkedlist contains data
* Return: pointer to h->arg if lookup is ok
*/
char *get_node_by_prefix(char *prefix, LinkedList *h)
{
	char *value = NULL;

	while (h != NULL)
	{
		if (get_beginsWith(h->arg, prefix) && _strlen(prefix) == h->idx_sep)
		{
			value = (h->arg);
			break;
		}
		h = h->next;
	}
	return (value);
}
