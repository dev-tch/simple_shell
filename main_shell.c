#include "main_shell.h"
#include <stdio.h>
#include "strings.h"
#include "list.h"
#include "errors.h"

int read_command(char *program, char **user_input);
int add_args_cmd_to_list(char *program, char *user_input, info_cmd **head);
int handle_errors(char *program, char *command);

/**
 * main - entry point
 * @argc: number of arguments
 * @argv: list of arguments
 * @env: environnment variables
 * Return: (0==> ok ) (1 ==> ko)
 */
int main(int argc, char *argv[], char **env)
{
	/*local variables */
	int loop = 1;
	info_cmd *head = NULL;
	char *user_input, *program;
	int read_ok = 1;
	int i;

	if (argc >= 0)
	{
		program = argv[0];
	}
	while (loop)
	{
		display_prompt("($)", 4);
		read_ok = read_command(program, &user_input);
		if (!read_ok)
		{
			continue;
		}

		i = add_args_cmd_to_list(program, user_input, &head);
		if (i > 0 && head != NULL)
		{
			if (handle_errors(program, head->arg) == 1)
			{
				/*lunch the excution of command with process child*/
				loop = lunch_shell_execution(program, head, env);
			}
		}
		if (head != NULL)
		{
			free_list(head);
			head = NULL;
		}
		if (user_input != NULL)
		{
			free(user_input);
			user_input = NULL;
		}
	}
	return (0);
}
/**
* read_command - read input from stdin
* @program: name of shell program
* @user_input: pointer to pointer char
* Return: (0==> read is ko) (1 ==> read is ok)
*/
int  read_command(char *program, char **user_input)
{
	size_t n = 0;
	ssize_t nb_bytes = 0;
	/** local variables declaration  */
	nb_bytes = getline(user_input, &n, stdin);

	if (nb_bytes == -1)
	{       print_error(program, GETLINE_ERROR, NEW_ERROR);
		return (0);
	}
	if (nb_bytes  <= 1)
	{
		free(*user_input);
		*user_input = NULL;
		return (0);
	}
	/* delete new line character */
	if ((*user_input)[nb_bytes - 1] == '\n')
	{
		(*user_input)[nb_bytes - 1] = '\0';
	}
	return (1);
}
/**
* add_args_cmd_to_list - save name commmant and its arguments in list
* @program: name of shell program
* @user_input: pointer to input entered by user
* @head: pointer to pointer to the head node of list
* Return: number of nodes added to list
*/
int add_args_cmd_to_list(char *program, char *user_input, info_cmd **head)
{
int i = 0;
char *delimiters = " \n\r\t";
char *token;
info_cmd *inserted_node = NULL;

token = split(user_input, delimiters);
while (token != NULL)
{
	if (!is_empty(token))
	{
		inserted_node = add_node_end(head, token);
		if (inserted_node == NULL)
		{
			print_error(program, MALLOC_ERROR, NEW_ERROR);
			break;
		}
		i++;
	}
	token = split(NULL, delimiters);
}
return (i);
}
/**
* handle_errors - check if command is valid
* @program: name of shell program
*@command: name of command
*Return: void
*/
int handle_errors(char *program, char *command)
{
	struct stat st;
	int err = 0;

	/*check if  file exist*/
	err = stat(command, &st);
	if (err == -1)
	{       print_error(program, errno, STD_ERROR);
		return (0);
	}

	/*check If file is excutable */
	err = access(command, X_OK);
	if (err == -1)
	{
		print_error(program, errno, STD_ERROR);
		return (0);
	}
	return (1);
}
