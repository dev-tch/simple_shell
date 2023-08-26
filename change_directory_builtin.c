#include <stdlib.h>
#include <unistd.h>
#include "new_types.h"
#include "common.h"
#include "strings.h"

char *get_value(char *var_name, LinkedList **env_t);
int update_value(char *var_name, char *var_value, LinkedList **env_l);

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
	char *home = NULL, *pwd = NULL, *oldpwd = NULL;
	char dest[256];

	/*char cwd[256];*/
	int ret = 1;
	/*char *new_dir;*/
	/*char old_dir[256];*/
	/*unused parameters*/
	(void)prg;
	(void) env;
	(void)alia_l;
	/*recuperation de PWD*/
	/*recuperation de HOME*/
	/*la ==1*/
	/*la > 1*/
	home = get_value("HOME", env_l);
	pwd  = get_value("PWD", env_l);
	if (la == 1 && home != NULL)
		_strcpy(dest, home);
	else if (la > 1)
	{
		if (_strcmp(args[1], "-") == 0 && oldpwd != NULL)
			_strcpy(dest, oldpwd);
		else if (args[1] != NULL)
			_strcpy(dest, args[1]);
	}
	if (dest != NULL && !is_empty(dest))
		ret = chdir(dest);
	if (ret == 0) /*on success*/
	{
		/*update_value("*/
		update_value("OLDPWD", pwd, env_l);
		update_value("PWD", dest, env_l);
		/*update pwd*/
	}
	return (1);
}

/**
* get_value - search env variable and return its value
* @var_name: environnement variable name
* @env_l: list contains environnments
* Return: pointer to node in env_l
*/
char *get_value(char *var_name, LinkedList **env_l)
{
	LinkedList *tmp = *env_l;
	int var_ok = 0, len = 0;
	char *var_value  = NULL;

	len = _strlen(var_name);
	while (tmp != NULL)
	{
		var_ok = get_beginsWith(tmp->arg, var_name);
		if (var_ok)
		{
			var_ok = 1;
			var_value = (tmp->arg + len + 1);
			break;
		}
		tmp = tmp->next;
	}
	return (var_value);
}
/**
* update_value - assign new value to environnement variable
* @var_name: environnement variable name
* @var_value: new value used for update
* @env_l: list of envirronnements
* Return: (1 if update ok) else (0)
*/
int update_value(char *var_name, char *var_value, LinkedList **env_l)
{
	LinkedList *tmp = NULL;
	int var_ok = 0;
	char *old_data = NULL;
	char *dest = NULL;

	tmp = *env_l;
	while (tmp != NULL)
	{
		var_ok = get_beginsWith(tmp->arg, var_name);
		if (var_ok)
		{
			/*if variable is alreday exist ==>  update*/
			dest = (char *) malloc(_strlen(var_name) + 1 + _strlen(var_value) + 1);
			_strcpy(dest, var_name);
			_strcat(dest, "=");
			_strcat(dest, var_value);
			old_data = tmp->arg;
			tmp->arg  = _strdup(dest);
			tmp->len  = _strlen(dest);
			free(dest);
			dest = NULL;
			free(old_data);
			old_data = NULL;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
