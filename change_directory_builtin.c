#include <stdlib.h>
#include <unistd.h>
#include "new_types.h"
#include "common.h"
#include "strings.h"
#include <stdio.h>
#include <dirent.h>
#include "errors.h"
char *get_value(char *var_name, LinkedList **env_t);
int update_value(char *var_name, char *var_value, LinkedList **env_l);
int test_exist_dir(char *prg, char *path);
void update_env_var(char *dest, char *pwd, LinkedList **env_l);
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
char *home = get_value("HOME", env_l);
	char *oldpwd = get_value("OLDPWD", env_l);
	char dest[256], pwd[256];
	int ret = 1, flag = 0;

	dest[0] = '\0';
	_strcpy(pwd, get_value("PWD", env_l));
	(void) env, (void)alia_l;
	if (la == 1 && (home != NULL))
		_strcpy(dest, home);
	else if (la > 1)
	{
		if (_strcmp(args[1], "-") == 0)
		{
			if (oldpwd != NULL)
			_strcpy(dest, oldpwd);
			else if (pwd != NULL)
			_strcpy(dest, pwd);
			flag = 1;
		}
		else if (args[1] != NULL)
			_strcpy(dest, args[1]);
	}
	if (dest[0] != '\0')
	{
		if (!test_exist_dir(prg, dest))
			return (1);
		ret = chdir(dest);
		if (flag)
		{
			write(STDOUT_FILENO, dest, _strlen(dest));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	if (ret == 0) /*on success*/
	{
		update_env_var(dest, pwd, env_l);
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

/**
* test_exist_dir - method to test existence of dir
* @prg: initial shell program
* @path: dir to test
* Return: (0:ko)(1:ok)
*/
int test_exist_dir(char *prg, char *path)
{
	DIR *dir;
	char *msg = ": 1: cd: can't cd to ";
	int fderr = 2;
	int res = 1;

	dir = opendir(path);
	errno = 0;
	if (dir == NULL)
	{
		write(fderr, prg, _strlen(prg));
		write(fderr, msg, _strlen(msg));
		write(fderr, path, _strlen(path));
		write(fderr, "\n", 1);
		res = 0;
	}
	else
		closedir(dir);
	return (res);
}
/**
* update_env_var - maj env variables
* @dest: new PWD
* @pwd: new OLDPWD
* @env_l: list environnements
* Return: void
**/
void update_env_var(char *dest, char *pwd, LinkedList **env_l)
{
	if (dest != NULL)
		update_value("PWD", dest, env_l);
	if (pwd != NULL)
	update_value("OLDPWD", pwd, env_l);
}
