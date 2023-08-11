#include "new_types.h"
#include "strings.h"
#include "main_shell.h"
#include <stdio.h>
/**
* add_node_end - add node at the the list
* @head: pointer of pointers contains the pointer to each node
*@str: string to be added at the new node
*Return: the adress of new node
*/

info_cmd *add_node_end(info_cmd **head, const char *str)
{
	info_cmd  *new_node;
	info_cmd  *temp;

	new_node = malloc(sizeof(info_cmd));
	if (new_node == NULL)
	{
		return (NULL);
	}
	/*initilize next node */
	new_node->next = NULL; /*fix the problem of double free dtected*/
	if (str != NULL)
	{
		new_node->arg = _strdup(str);
		if (new_node->arg == NULL)
		{
			free(new_node);
			return (NULL);
		}
	new_node->len = _strlen(new_node->arg);
	} /*if str!=NULL*/

	else
	{
		new_node->arg  = NULL;
		new_node->len  = 0;
	}
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
	temp->next = new_node;
	}
	return (new_node);
}
/**
* free_list - empty linked list
* @head: pointer of pointers to nodes
*Return: void
*/
void free_list(info_cmd *head)
{
	info_cmd *temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->arg);
		temp->arg = NULL;
		free(temp);
	}
}
/**
* add_node - insert new node at the beginning of list
* @head: pointer to the nodes of list
* @str: string of new node
* Return: pointer to head of list
*/
info_cmd *add_node_first(info_cmd **head, const char *str)
{
info_cmd *new_node;
new_node = malloc(sizeof(info_cmd));
if (new_node == NULL)
return (NULL);
if (str != NULL)
{
new_node->arg = _strdup(str);
if (new_node->arg == NULL)
{
free(new_node);
return (NULL);
}
new_node->len = strlen(new_node->arg);
}
else
{
new_node->arg = NULL;
new_node->len = 0;
}
if (head != NULL)
{
new_node->next = *head;
*head = new_node;
}
else
head = &new_node;
return (new_node);
}


