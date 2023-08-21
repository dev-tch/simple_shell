#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "new_types.h"

/**
 * Change_dir - change the current directory.
 * @prg: The program name. example ./shell
 * @la: An integer argument.
 * @args: An array of string arguments.
 * @env: An array of environment variable strings.
 * @env_l: A pointer to a linked list for environment variables.
 * @alia_l: A pointer to a linked list for aliases.
 * @Return: Return an integer status code indicating success or failure.
 */
int change_dir(char *prg, int la, char **args, char **env,
LinkedList **env_l, LinkedList **alia_l)
{
	/*unused parameters*/
	(void)prg;
	la = (la == 0) ? 0 : la;
	(void) args;
	(void) env;
	(void)env_l;
	(void)alia_l;

	return (1);
}

	char *new_dir;

	if (la == 1)
	{
		/*No argument provided, change to $HOME*/
		new_dir = getenv("HOME");
	}
		else if (strcmp(args[1], "-") == 0)
	{
		/*Handle cd - */
		new_dir = getenv("OLDPWD");
	}
		else
	{
		new_dir = args[1];
	}

	char old_dir[256];

	if (getcwd(old_dir, sizeof(old_dir)) == NULL)
	{
		perror("getcwd");
		return (-1);
	}

	if (chdir(new_dir) != 0)
	{
		perror("chdir");
		return (-1);
	}

	if (setenv("OLDPWD", old_dir, 1) != 0)
	{
		perror("setenv");
		return (-1);
	}

	if (setenv("PWD", new_dir, 1) != 0)
	{
		perror("setenv");
		return (-1);
	}

	return (0);
}
