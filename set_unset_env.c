#include "new_types.h"
#include <stddef.h>
#include "strings.h"
#include <stdlib.h>
#include "list.h"
#include "errors.h"
#include "common.h"

/**
* var_exist - check is variable found in environnement
* @var_name: name of variable
* @var_value: content of variable
* @env_t: list contains environnments
* Return: (0 variable not found) ( 1 variable exist)
*/
int var_exist(char *var_name, char *var_value, info_cmd **env_t)
{
	info_cmd *tmp = NULL;
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
* set_env -  builtin function to add or modify env variable
* @prg: initila program
* @la: number of arguments of command
* @arg: array of arguments of command
* @env: array of environnments variables
* @env_t: list contains environnements
* Return: (1 to continue the loop in main_shell.c)
*/
int set_env(char *prg, int la, char  **arg, char **env, info_cmd **env_t)
{
	int ret = 0;
	char *dest = NULL;
	/*error if illigal arguments*/
	/*get the index of variable from env*/
	/*unused parameters*/
	(void)env;
	if (la != 3)
	{
		print_error(prg, ILLIGAL_ARG, NEW_ERROR);
		return (1);
	}
	ret = var_exist(arg[1], arg[2], env_t);
	/*if vraiable is new ===> create*/
	if (ret == 0)
	{
		dest = (char *) malloc(_strlen(arg[1]) + 1 + _strlen(arg[2]) + 1);
		_strcpy(dest, arg[1]);
		_strcat(dest, "=");
		_strcat(dest, arg[2]);
		add_node_end(env_t, dest);
		free(dest);
	}
	return (1);
}
/*unset builtin*/
