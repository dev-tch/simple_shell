#include "strings.h"
#include "new_types.h"
#include "errors.h"
#include <stdio.h>
#include "cleanup.h"
#include <stdlib.h>
#include <unistd.h>
#include "common.h"

/**
* shell_exit - exit interactive mode in shell
* @prg: the initial program that lunch main - example ./shell
* @la: number of arguments in command
* @args: arguments of command
* @env: environnement variables
* @env_t: list contains environnements
* Return: (0 to leave the loop) ( values differnt to zero to continue the loop)
*/
int shell_exit(char *prg, int la,  char **args, char **env, info_cmd **env_t)
{
	int num = 0;

	/* declare parameters as unused*/
	prg = (prg == NULL) ?  NULL : prg;
	env = (env == NULL) ?  NULL : env;
	env_t = (env_t == NULL) ?  NULL : env_t;

	if (la == 1)
	{
		cleanupArray(la, &args);
		cleanupList(env_t);
		cleanupArray(list_len(*env_t), &env);
		exit(EXIT_DONE);
	}
	else if (la >= 2)
	{
		/*convert cmd_args[1] to int */
		num = _atoi(args[1]);
		if (num == 0 && _strcmp(args[1], "0") != 0)
		{
			print_err_plus(prg, ILLIGAL_EXIT_NUMBER, NEW_ERROR, args[1]);
		}
		else
		{
			cleanupList(env_t);
			cleanupArray(la, &args);
			cleanupArray(list_len(*env_t), &env);
			exit(num);
		}
	}
	return (1);
}
/**
* lunch_builtin - excutes builtin function in shell
* @prg: the initial program that lunch main - example ./shell
* @la: number of arguments in command
* @arg: arguments of command
* @env: environnement variables
* @env_t: list contains environnements
* Return: (0 to leave the loop) ( value differnt to zero to continue the loop)
*/
int lunch_builtin(char *prg, int la, char  **arg, char **env, info_cmd **env_t)
{
	int i = 0, number_of_builtin = 0;
	int ret = NOT_BUILT_IN;
	char *names_builtin[] = {
		"exit",
		"env",
		"setenv",
		"unsetenv"
	};

	int (*b_f[]) (char *prg, int la, char **arg, char **env, info_cmd **env_t) = {
		&shell_exit,
		&print_env,
		&set_env,
		&unset_env
	};

	/*if command empty string with continue interactive mode*/
	if (is_empty(arg[0]))
	{
		return (1);
	}
	number_of_builtin = (sizeof(names_builtin) / sizeof(char *));
	for (i = 0 ; i < number_of_builtin ; i++)
	{
		if (_strcmp(arg[0], names_builtin[i]) == 0)
		{
			ret = 0;
			ret = ((*b_f[i])(prg, la, arg, env, env_t));
		}
	}

	return (ret);
}

/**
* is_builtin - check if command is builtin function of shell
* @name_cmd: the command name
* Return: (1 ==> builtin function)(0==> non builtin function)
*/
int is_builtin(char *name_cmd)
{
	int i = 0, number_of_builtin = 0, ret = 0;

	char *names_builtin[] = {
		"exit",
		"env",
		"setenv",
		"unsetenv"
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
* @la: number of arguments in command
* @arg: arguments of command
* @env: environnement variables
* @env_t: list contains environnemnts
* Return: Number of environment variables, or 0 on error.
*/
int print_env(char *prg, int la, char **arg, char **env, info_cmd **env_t)
{
	int i = 0, len = 0, fd = 1;
	char *buf = NULL;
	(void)arg;
	(void)prg;
	la = (la == 0) ? 0 : la;
	env_t = (env_t == NULL) ?  NULL : env_t;
	/*fflush(stdout);*/
	while (env[i] != NULL)
	{
		len = _strlen(env[i]);
		if (len >= 0)
		{
			buf = (char *) malloc(len + 2);
			if (buf == NULL)
			{
				print_error(prg, MALLOC_ERROR, NEW_ERROR);
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
