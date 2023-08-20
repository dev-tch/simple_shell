#include "errors.h"
#include "new_types.h"
#include "list.h"
/**
* cleanupArray - clean ressources used
* @len_args: len of arguments in command
* @args: arguments of command
* Return: void
*/
void cleanupArray(int len_args, char ***args)
{
	/*declaration local variables */
	int i = 0;
	/* condition to ovoid error double free detected*/
	if (args == NULL || *args == NULL)
		return;

	for (i = 0 ; i < len_args ; ++i)
	{
		if ((*args)[i] != NULL)
		{
			free((*args)[i]);
			(*args)[i] = NULL;
		}
	}
	if (*args != NULL)
	{
		free(*args);
		*args = NULL;
	}
}

/**
* cleanupInput - clean ressources used
* @input: data entered to stdin
* @n: the satus variable that tracks buffer input
* Return: void
*/
void cleanupInput(char **input, size_t *n)
{
	/* condition to ovoid error double free detected*/
	if (input == NULL || *input == NULL)
		return;

	if (*input != NULL)
	{
		free(*input);
		*input = NULL;
	}
	if (n != NULL)
	*n = 0;
}

/**
* cleanupList - clean ressources used
* @head: list of nodes
* Return: void
*/
void cleanupList(LinkedList **head)
{
	/* condition to ovoid error double free detected*/
	if (head == NULL || *head == NULL)
		return;

	free_list(*head);
	 *head = NULL;
}
