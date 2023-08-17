#include "strings.h"
#include "new_types.h"
#include "errors.h"
#include <stdio.h>
#include "cleanup.h"
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

int print_env(char *prg, int len_args, char **cmd_args, char **env);
/**
* test - template for built in functions
* @prg: the initial program that lunch main - example ./shell
* @len_args: number of arguments in command
* @cmd_args: arguments of command
* @env: environnement variables
* Return: (0 to leave the loop) ( value differnt to zero to continue the loop)
*/
int test(char *prg, int  len_args,  char **cmd_args, char **env)
{
	/* unused parameters */
	(void)prg;
	(void)cmd_args;
	(void)env;
	len_args = (len_args == 0) ? 0 : 1;
	/*end unused parameters*/

	/*if error print the error and on return */
	print_error("test", 100, NEW_ERROR);

	/*if echec that deamnds to quit the loop of main_shell*/
	/* ==> return 0*/

	/*return 1 or value differnt to zero to let the loop in main_shell*/
	return (1);
}
/**
* shell_exit - exit interactive mode in shell
* @prg: the initial program that lunch main - example ./shell
* @len_args: number of arguments in command
* @cmd_args: arguments of command
* @env: environnement variables
* Return: (0 to leave the loop) ( value differnt to zero to continue the loop)
*/
int shell_exit(char *prg, int len_args,  char **cmd_args, char **env)
{
	int num = 0;

	/* declare parameters as unused*/
	prg = (prg == NULL) ?  NULL : prg;
	env = (env == NULL) ?  NULL : env;

	if (len_args == 1)
	{
		cleanup2(len_args, &cmd_args);
		exit(EXIT_DONE);
	}
	else if (len_args >= 2)
	{
		/*convert cmd_args[1] to int */
		num = _atoi(cmd_args[1]);
		if (num == 0 && _strcmp(cmd_args[1], "0") != 0)
		{
			print_err_plus(prg, ILLIGAL_EXIT_NUMBER, NEW_ERROR, cmd_args[1]);
		}
		else
		{
			cleanup2(len_args, &cmd_args);
			exit(num);
		}
	}
	return (1);
}
/**
* lunch_builtin - excutes builtin function in shell
* @prg: the initial program that lunch main - example ./shell
* @len_args: number of arguments in command
* @cmd_args: arguments of command
* @env: environnement variables
* Return: (0 to leave the loop) ( value differnt to zero to continue the loop)
*/
int lunch_builtin(char *prg, int len_args, char  **cmd_args, char **env)
{
	int i = 0, number_of_builtin = 0;
	int ret = NOT_BUILT_IN;
	char *names_builtin[] = {
		"test",
		"exit",
		"env"
	};

	int (*builtin_func[]) (char *prg, int len_args, char **cmd, char **env) = {
		&test,
		&shell_exit,
		&print_env
	};

	/*if command empty string with continue interactive mode*/
	if (is_empty(cmd_args[0]))
	{
		return (1);
	}
	number_of_builtin = (sizeof(names_builtin) / sizeof(char *));
	for (i = 0 ; i < number_of_builtin ; i++)
	{
		if (_strcmp(cmd_args[0], names_builtin[i]) == 0)
		{
			ret = 0;
			ret = ((*builtin_func[i])(prg, len_args, cmd_args, env));
		}
	}

	return (ret);
}
/**
* print_env: Function to print environment variables and their count.
* @prg: the initial program that lunch main - exp ./shell
* @len_args: number of arguments in command
* @cmd_args: arguments of command
* @env: environnement variables
* @Return: Number of environment variables :w
processed, or 0 on error.
*/
int print_env(char *prg, int len_args, char **cmd_args, char **env)
{
	char buffer[1024]; /* Buffer to hold the environment variable strings*/
	char *current_env = *env;
	size_t length = 0;
	char env_count[] = "Env[]: ";
	ssize_t bytes_written;
	int count = 0;
	len_args = (len_args == 0) ? 0 : 1;
	(void)cmd_args;
	
	/* Check if program or env is NULL*/
	if (prg == NULL || env == NULL)
	{
		return (0); /*Return 0 in case of an error*/
	}

	/*Loop through each environment variable*/
	while (*env != NULL)
	{
	/*Manually concatenate the environment variable information into buffer*/
	/*Copy the "Env[count]" part*/
		env_count[4] = count / 10 + '0';
		env_count[5] = count % 10 + '0';
		length += write(STDOUT_FILENO, env_count, 8);
	/*Copy the environment variable string*/
		while (*current_env != '\0' && length < sizeof(buffer) - 1)
		{
			buffer[length++] = *current_env++;
		}
	/* Add a newline character and null-terminate the string*/
		if (length < sizeof(buffer))
		{
			buffer[length++] = '\n';
		}
	/*Write the manually formatted string to standard output*/
		bytes_written = write(STDOUT_FILENO, buffer, (size_t)length);

		if (bytes_written < 0)
		{
			return (0); /* Error in writing*/
		}
		count++;
		env++;
	}
	return (count);
}
