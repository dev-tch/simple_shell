#include "main_shell.h"
#include <stdio.h>
#include "strings.h"
#include "list.h"

int read_command(char **user_input);
int add_args_cmd_to_list(char *user_input, info_cmd **head);
void handle_errors(char *command);

/**
 * main - entry point
 * @argc: number of arguments
 * @argv: list of arguments
 * Return: (0==> ok ) (1 ==> ko)
 */
int main(int argc, char *argv[])
{
	/*local variables */
	int loop = 1;
	info_cmd *head = NULL;
	char *user_input;
	int read_ok = 1;
	int i;

	/*fix to suppress the warning about unused attributes*/
	(void)argc;
	(void)argv;
	while (loop)
	{
		display_prompt("($)", 4);
		read_ok = read_command(&user_input);
		if (!read_ok)
		{
			continue;
		}

		i = add_args_cmd_to_list(user_input, &head);
		if (i > 0 && head != NULL)
			handle_errors(head->arg);
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
* @user_input: pointer to pointer char
* Return: (0==> read is ko) (1 ==> read is ok)
*/
int  read_command(char **user_input)
{
	size_t n = 0;
	ssize_t nb_bytes = 0;
	/** local variables declaration  */
	nb_bytes = getline(user_input, &n, stdin);

	if (nb_bytes == -1)
	{
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
* @user_input: pointer to input entered by user
* @head: pointer to pointer to the head node of list
* Return: number of nodes added to list
*/
int add_args_cmd_to_list(char *user_input, info_cmd **head)
{
int i = 0;
char *delimiters = " \n\r\t";
char *token;

token = strtok(user_input, delimiters);
while (token != NULL)
{
	if (!is_empty(token))
	{
		add_node_end(head, token);
		i++;
	}
	token = strtok(NULL, delimiters);
}
return (i);
}
/**
* handle_errors - check if command is valid
*@command: name of command
*Return: void
*/
void handle_errors(char *command)
{       /* test there is \n in command that's why our file not exist */
	struct stat st;
	int err;

	err = stat(command, &st);
	if (err == -1)
	{
		printf("./shell: No such file or directory");
	}
}
