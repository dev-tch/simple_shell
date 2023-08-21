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
 * Return: Return an integer status code indicating success or failure.
 */
int change_dir(char *prg, int la, char **args, char **env,
LinkedList **env_l, LinkedList **alia_l)
{
	char *new_dir;
	char old_dir[256];
	/*unused parameters*/
	(void)prg;
	(void) env;
	(void)env_l;
	(void)alia_l;

	if (la == 1)
		new_dir = getenv("HOME"); /*No argument provided, change to $HOME*/
	else if (strcmp(args[1], "-") == 0)
		new_dir = getenv("OLDPWD");/*Handle cd - */
	else
		new_dir = args[1];
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
	return (1);
}
