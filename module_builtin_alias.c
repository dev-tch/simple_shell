#include "new_types.h"
#include "strings.h"
#include "common.h"
#include "list.h"
#include "stdlib.h"
#include "helper_functions.h"

void alias_action(char *prg, int id_sep, char *alias_var, LinkedList **alia_l);

/**
* doAlias - handle alias of shell
* @prg: initial program
* @la: length of arguments
* @args: arguments
* @env: double pointer contains envs
* @env_l: list contains envs
* @alia_l: list contains alias
* Return: (no more loop) (1 continue the loop) (-1 break the loop)
*/
int doAlias(char *prg, int la,  char **args, char **env, LinkedList **env_l,
LinkedList **alia_l)
{
	int i = 0, id_sep = 0;

	/*unused parameters*/
	env     = (env == NULL) ? NULL : env;
	env_l   = (env == NULL) ? NULL : env_l;

	if (la == 1)
	{
		print_list(prg, *alia_l);
	}
	else
	{
		for (i = 1 ; i < la ; i++)
		{
			id_sep = get_index_sep(args[i], '=');
			alias_action(prg, id_sep, args[i], alia_l);
		}
	}

	return (1);
}

/**
* alias_exist - check if name of alias exist in list
* @var_name: name of alias
* @var_value: value of alias
* @alia_l: linkedlist contains alias info
* Return: (1: alias updated) (0: alias not found we have to create it)
*/
int alias_exist(char *var_name, char *var_value, LinkedList **alia_l)
{
	LinkedList *tmp = NULL;
	int var_ok = 0;
	char *old_data = NULL;
	char *dest = NULL;

	tmp = *alia_l;
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
* alias_action - process the alias function
* @prg: initilal program shell
* @id_sep: index of seperator "=" between name && value of alias
* @alias_data: key=value of alias
* @alia_l: linkedlist contains alias info
* Return: void
*/
void alias_action(char *prg, int id_sep, char *alias_data, LinkedList **alia_l)
{
	/*int alia_found = 0;*/
	int var_alia_found = 0;

	char *value = NULL;
	char *name  = NULL;

	if (id_sep == 0)
	{
		value = get_node_by_prefix(alias_data, *alia_l);
		if (value != NULL)
			printMsgWithNewLine(prg, value);
		else
			print_error_alias(prg, alias_data);
	}
	else
	{
		value = alias_data + id_sep + 1;
		name = (char *) malloc(id_sep + 1);
		_strncpy(name, alias_data, (id_sep));
		var_alia_found = alias_exist(name, value, alia_l);
		free(name);
		if (var_alia_found == 0)
		{
			add_node_end(alia_l, alias_data);
		}
	}
}
