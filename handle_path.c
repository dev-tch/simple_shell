#include <stdio.h>
#include "strings.h"
#include <stdlib.h>
#include "new_types.h"
#include "list.h"
#include <string.h>
#include "errors.h"
#include <sys/stat.h>
/**
* get_beginsWith - search pattern in string and return index
* @src: string to apply the search in it
* @pattern: string pattern used for serach
* Return: (0 ==> not found)(or index )
*/
int get_beginsWith(char *src, char *pattern)
{
	int i = 0;

	while (pattern[i] != '\0')
	{
		if (src[i] == '\0' || src[i] != pattern[i])
		{
			return (0);
		}
		i++;
	}
	return (i);
}
/**
* get_path_value - return the variable PATH from env
* @env: array  of environnement variables
* Return: (NULL ==> nor var PATH) (strings: value of PATH)
*/

char *get_path_value(char **env)
{
	char *var_path = "PATH=", *dest = NULL, *buf_path = NULL;
	int i = 0, index = 0, len = 0;

	while (env[i] != NULL)
	{
		dest = env[i];
		index = get_beginsWith(env[i], var_path);
		if (index != 0)
		{
			dest += (index);
			break;
		}
		i++;
	}
	if (dest == NULL || *dest == '\0')
		return (NULL);
	/*allocation of memorory to path variable */
	len = _strlen(dest);
	buf_path = (char *) malloc(len + 1);
	if (buf_path == NULL)
		return (NULL);
	_strcpy(buf_path,  dest);
	return (buf_path);
}

/**
* convert_path_to_list - parse the path value to list
* @prg: initial program that lunch shell
* @env: array of environnements variables
* @head_path: list contains  folders of variable PATH
* Return: (0==> no node in head_path) ( n: number of node in head_path)
*/
int convert_path_to_list(char *prg, char **env,  info_cmd **head_path)
{
	int i = 0;
	char *delimiters = ":";
	char *token = NULL;
	info_cmd *inserted_node = NULL;
	char *path_ptr = NULL;

	/*test if path ok*/
	path_ptr = get_path_value(env);
	if (path_ptr == NULL)
		return (0);

	token = strtok(path_ptr, delimiters);
	while (token != NULL)
	{
		if (!is_empty(token))
		{
			inserted_node = add_node_end(head_path, token);
			if (inserted_node == NULL)
			{
				print_error(prg, MALLOC_ERROR, NEW_ERROR);
				break;
			}
			i++;
		}
		token = strtok(NULL, delimiters);
	}
	/*after the path converted to list we have to free the allocated memory*/
	if (path_ptr != NULL)
		free(path_ptr);
	return (i);
}
/**
* lookup_in_path - search if command exist in each node of head_path
* @name_cmd: command name
* @head_path: list contains folders
* Return: pointer to found path
*/
char *lookup_in_path(char *name_cmd, info_cmd *head_path)
{

	/*loop  all nodes of head_path (all folders)*/
	static char fold_file[100];
	struct stat st;
	int file_ok = 0;
	int exec_ok = 0;

	char *fold = NULL;

	while (head_path != NULL)
	{
		_strcpy(fold_file, head_path->arg);
		_strcat(fold_file, "/");
		_strcat(fold_file, name_cmd);
		head_path = head_path->next;
		file_ok = stat(fold_file, &st);
		if (file_ok != 0)
		{
			continue;
		}
		exec_ok = access(fold_file, X_OK);
		if (exec_ok != 0)
		{
			continue;
		}
		{
			fold = fold_file;
			break;
		}
	}
	return (fold);
}

