#include "errors.h"
#include "new_types.h"
#include "list.h"
/**
* cleanup - clean ressources used
* @user_input: the buffer used to hold the content of input
* @head: the list contains info of command
* @len_args: len of arguments in command
* @args: arguments of command
* Return: void
*/
void cleanup(char **user_input, info_cmd **head, int len_args, char ***args)
{
	/*declaration local variables */
	int i = 0;

	if (*head != NULL)
	{
		free_list(*head);
		*head = NULL;
	}

	if (*user_input != NULL)
	{
		free(*user_input);
		*user_input = NULL;
	}

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
* cleanup1 - clean ressources used
* @user_input: the buffer used to hold the content of input
* @head: the list contains info of command
* Return: void
*/
void cleanup1(char **user_input, info_cmd **head)
{

	if (*head != NULL)
	{
		free_list(*head);
		*head = NULL;
	}

	if (*user_input != NULL)
	{
		free(*user_input);
		*user_input = NULL;
	}

}

/**
* cleanup2 - clean ressources used
* @len_args: len of arguments in command
* @args: arguments of command
* Return: void
*/
void cleanup2(int len_args, char ***args)
{
	/*declaration local variables */
	int i = 0;

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
