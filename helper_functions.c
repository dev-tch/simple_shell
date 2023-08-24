#include "strings.h"
#include "errors.h"
#include "list.h"
#include <string.h>
#include "common.h"
/**************** methode to write a message with new line */
/**
* save_commands - save multiple commands in linkedlist
* @cmds: list that contains commands
* @input: string of commands sepreated by (;)
* Return: number of commands
*/
int save_commands(LinkedList **cmds, char *input)
{
	int idx = 0;
	char *token;

	int i = 0, j = 0;

	if (input == NULL)
	{
		return (0);
	}

	if (is_empty(input))
	{
		return (0);
	}
	 /*bloc of code to analyse valgrind problem*/
	if (*input == '#')
	{
		return (0);
	}
	while (input[j] !=  '\0')
	{
		idx = (input[j] == '#');
		if (idx == 1)
			break;
		j++;
	}
	if (idx == 1)
	{
		input  = strtok(input, "#");
	}
	token = strtok(input, ";");

	while (token != NULL)
	{
		add_node_end(cmds, token);
		i++;
		token = strtok(NULL, ";");
	}

	return (i);
}

/**
* printMsg - print node in list alias
* @alia: list contains alias
* Return: void
*/
void printMsg(LinkedList *alia)
{
	int len_msg = 0, pos_sep = 0;
	int fd = 1; /*stdout*/

	len_msg = _strlen(alia->arg);
	pos_sep = alia->idx_sep;
	if (len_msg > 0)
	{
		write(fd, alia->arg, pos_sep);
		write(fd, "='", 2);
		write(fd, (alia->arg + pos_sep + 1), (len_msg - pos_sep - 1));
		write(fd, "'\n", 2);
	}

}

/**
* nodeBeginsWithVar - test if item list begins with prefix
* @prefix: name of alias
* @h: list of alias
* Return: item of alias
*/
char *nodeBeginsWithVar(char *prefix, LinkedList *h)
{
	char *value = NULL;
	LinkedList *temp = NULL;

	while (h != NULL)
	{
		if (get_beginsWith(h->arg, prefix) && _strlen(prefix) == h->idx_sep)
		{
			value = (h->arg);
			temp = h;
			temp->next = NULL;
			printMsg(temp);
			break;
		}
		h = h->next;
	}
	return (value);
}

/**
* print_alia_reverse - print nodes of list alia in reverse order
* @h: list alias
* Return: void
*/
void print_alia_reverse(LinkedList *h)
{
	LinkedList *new_head = NULL;
	LinkedList *current  = h;
	LinkedList *temp;

	while (current != NULL)
	{
		temp = current->next;
		current->next = new_head;
		new_head = current;
		current = temp;
	}

	while (new_head != NULL)
	{
		printMsg(new_head);
		new_head = new_head->next;
	}
}

