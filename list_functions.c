#include "new_types.h"
#include "strings.h"
#include "main_shell.h"

/**
* add_node_end - add node at the list
* @head: pointer of pointers contains the pointer to each node
*@str: string to be added at the new node
*Return: the adress of new node
*/

LinkedList *add_node_end(LinkedList **head, const char *str)
{
	LinkedList  *new_node, *temp;

	new_node = malloc(sizeof(LinkedList));
	if (new_node == NULL)
		return (NULL);
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
		new_node->idx_sep = get_index_sep(new_node->arg, '=');
	} /*if str!=NULL*/

	else
	{
		new_node->arg  = NULL;
		new_node->len  = 0;
		new_node->idx_sep = 0;
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
void free_list(LinkedList *head)
{
	LinkedList *temp;

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
LinkedList *add_node_first(LinkedList **head, const char *str)
{
	LinkedList *new_node;

	new_node = malloc(sizeof(LinkedList));

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
	new_node->len = _strlen(new_node->arg);
	new_node->idx_sep = get_index_sep(new_node->arg, '=');
	}
	else
	{
		new_node->arg = NULL;
		new_node->len = 0;
		new_node->idx_sep = 0;
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

/**
* list_len - calculates the number of elemnts in linked list
* @h: pointer to head  of list
* Return: size of list
*/
int list_len(const LinkedList *h)
{
	int nb = 0;

	while (h != NULL)
	{
		nb++;
		h = h->next;
	}
	return (nb);
}

/**
* list_to_array - convert list to array
* @h: head of list
* Return: array of constant pointers
*/
char **list_to_array(LinkedList *h)
{
	int nb_nodes = 0, index = 0, i = 0;
	char **cmd_args;

	/*get lenght of list*/
	nb_nodes = list_len(h);
	if (nb_nodes == 0)
		return (NULL);
	/*allocate the memory for array*/
	cmd_args  = (char **)malloc((nb_nodes + 1) * sizeof(char *));
	if (cmd_args == NULL)
		return (NULL);
	/* copy nodes from list to new created array*/
	while (h != NULL)
	{
		cmd_args[index] = (char *)malloc(h->len + 1);
		if (cmd_args[index] == NULL)
		{
			for (i = 0; i < index; i++)
			{
				free(cmd_args[i]);
			}
			free(cmd_args);
			return (NULL);
		}
		_strcpy(cmd_args[index], h->arg);
		h = h->next;
		index++;
	}
	cmd_args[index] = NULL;
	return (cmd_args);
}

