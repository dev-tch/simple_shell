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
* is_builtin - check if command is builtin function of shell
* @name_cmd: command name
* Return: (1 ==> builtin func)(0==> non builtin func)
*/
int is_builtin(char *name_cmd)
{
	int i = 0, number_of_builtin = 0, ret = 0;

	char *names_builtin[] = {
		"exit",
		"env"
	};

	number_of_builtin = (sizeof(names_builtin) / sizeof(char *));
	if (is_empty(name_cmd))
	{
		return (0);
	}
		for (i = 0 ; i < number_of_builtin ; i++)
	{
		if (_strcmp(name_cmd, names_builtin[i]) == 0)
		{
			ret = 1;
			break;
		}
	}

	return (ret);
}
/**
* print_env - Function to print environment variables and their count.
* @prg: the initial program that lunch main - exp ./shell
* @len_args: number of arguments in command
* @cmd_args: arguments of command
* @env: environnement variables
* @Return: Number of environment variables, or 0 on error.
*/
int print_env(char *prg, int len_args, char **cmd_args, char **env)
{
	int i = 0, len = 0, fd = 1;
	char *buf = NULL;
	(void)cmd_args;
	(void)prg;
	len_args = (len_args == 0) ? 0 : len_args;
	/*fflush(stdout);*/
	while (env[i] != NULL)
	{
		len = _strlen(env[i]);
		if (len >= 0)
		{
			buf = (char *) malloc(len + 2);
			if (buf == NULL)
			{
			printf("malloc failed");
			break;
			}
			_strcpy(buf, env[i]);
			_strcat(buf, "\n");
			write(fd, buf, len + 1);
			if (buf != NULL)
			free(buf);
		}
		i++;
	}
	return (1);
}
