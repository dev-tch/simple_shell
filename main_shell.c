#include "main_shell.h"
#include <stdio.h>
#include "strings.h"
#include "list.h"
#include "errors.h"
#include "cleanup.h"

int read_command(char *program, char **user_input, size_t *n);
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
	char *user_input = NULL;
	char *program = NULL;
	int read_ok = 1;
	int i = 0;
	size_t n = 0;
	char **args = NULL;
	int len_args = 0;

	if (argc >= 0)
	{
		program = argv[0];
	}
	else
	{
		exit(EXIT_FAIL);
	}
	while (loop)
	{
		display_prompt("($) ", 5);
		read_ok = read_command(program, &user_input, &n);
		if (read_ok == -1)
		{
			display_prompt("\n", 1);
			break;
		}
		if (!read_ok)
		{
			continue;
		}

		i = add_args_cmd_to_list(program, user_input, &head);
		if (i > 0 && head != NULL)
		{

			args = list_to_array(head);
			len_args = list_len(head);
			/*test is builtin function of shell*/
			if (_strcmp(args[0], "exit") == 0)
			{
				cleanup1(&user_input, &head);
			}
			loop = lunch_builtin(program, len_args,  args, env);
			if (loop  == NOT_BUILT_IN)
			{
				if (handle_errors(program, args[0]) == 1)
				{
					/*lunch the excution of command with process child*/
					loop = lunch_shell_execution(program, len_args, args, env);
				}
			}
		}
		/*after each process of command*/
		cleanup(&user_input, &head, len_args, &args);
	}

	return (0);
}
/**
* read_command - read input from stdin
* @program: name of shell program
* @user_input: pointer to pointer char
* @n: address of variable that holds the size of input buffer
* Return: (0: next loop iteration) (-1: break loop )(1: continue task)
*/
int  read_command(char *program, char **user_input, size_t *n)
{
	/** local variables declaration  */
	ssize_t nb_bytes = 0;
	int ret = 1;

	nb_bytes = getline(user_input, n, stdin);
	ret = handle_CTRD(n, user_input);
	if (ret != 2)
	{
		return (ret);
	}
	if (nb_bytes == -1 && (errno != 0 && errno != 25))
	{
		print_error(program, errno, STD_ERROR);
		exit(EXIT_FAIL);
	}
	if (nb_bytes == -1 && (errno == 0 || errno == 25))
	{
		exit(EXIT_DONE);
	}
	/*this condition is logical*/
	/* read not ok cause minimum one character + \n*/
	if (nb_bytes  <= 1)
	{
		if (*user_input != NULL)
		{
			free(*user_input);
			*user_input = NULL;
		}
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
char *token = NULL;
info_cmd *inserted_node = NULL;

token = strtok(user_input, delimiters);
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
	token = strtok(NULL, delimiters);
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
