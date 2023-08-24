#include "new_types.h"
#include <stddef.h>
#include "strings.h"
#include <stdlib.h>
#include "list.h"
#include "errors.h"
#include "common.h"

/**
* var_exist - check is variable found in environnement
* @var_name: the name of variable
* @var_value: content of variable
* @env_t: list contains environnments
* Return: (0 variable not found) ( 1 variable exist)
*/
int var_exist(char *var_name, char *var_value, LinkedList **env_t)
{
	LinkedList *tmp = NULL;
	int var_ok = 0;
	char *old_data = NULL;
	char *dest = NULL;

	tmp = *env_t;
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
* var_exist2 - check is variable found and remove it
* @var_name: name of variable
* @env_t: list contains environnments
* Return: (0 variable not found) ( 1 variable exist)
*/
int var_exist2(char *var_name, LinkedList **env_t)
{
	LinkedList *tmp = *env_t;
	int var_ok = 0;
	LinkedList *old = NULL;

	while (tmp != NULL)
	{
		var_ok = get_beginsWith(tmp->arg, var_name);
		if (var_ok)
		{
			if (old == NULL)
			{
				*env_t = tmp->next;
			}
			else
			{
				old->next = tmp->next;
			}
			free(tmp);
			var_ok = 1;
			break;
		}
		old = tmp;
		tmp = tmp->next;
	}
	return (var_ok);
}
/**
* set_env -  builtin function to add or modify env variable
* @prg: initila program
* @la: number of arguments of command
* @arg: array of arguments of command
* @env: array of environnments variables
* @env_l: list contains environnements
* @alia_l: list contains alias
* Return: (1 to continue the loop in main_shell.c)
*/
int set_env(char *prg, int la, char  **arg, char **env,
LinkedList **env_l, LinkedList **alia_l)
{
	int ret = 0;
	char *dest = NULL;
	(void) alia_l;
	/*error if illigal arguments*/
	/*get the index of variable from env*/
	/*unused parameters*/
	(void)env;
	if (la != 3)
	{
		print_error(prg, ILLIGAL_ARG, NEW_ERROR);
		return (1);
	}
	ret = var_exist(arg[1], arg[2], env_l);
	/*if vraiable is new ===> create*/
	if (ret == 0)
	{
		dest = (char *) malloc(_strlen(arg[1]) + 1 + _strlen(arg[2]) + 1);
		_strcpy(dest, arg[1]);
		_strcat(dest, "=");
		_strcat(dest, arg[2]);
		add_node_end(env_l, dest);
		free(dest);
	}
	return (1);
}
/*unset builtin*/
/**
* unset_env -  builtin function to remove env variable
* @prg: initila program
* @la: number of arguments of command
* @arg: array of arguments of command
* @env: array of environnments variables
* @env_l: list contains environnements
* @alia_l: list contains alias
* Return: (1 to continue the loop in main_shell.c)
*/
int unset_env(char *prg, int la, char  **arg, char **env,
LinkedList **env_l, LinkedList **alia_l)
{
	int ret = 0;
	(void) alia_l;
	/*unused parameters*/
	(void)env;
	if (la != 2)
	{
		print_error(prg, ILLIGAL_ARG, NEW_ERROR);
		return (1);
	}
	ret = var_exist2(arg[1], env_l);
	if (ret == 0)
	{
		print_error(prg, VAR_ENV_NOT_FOUND, NEW_ERROR);
	}
	return (1);
}
