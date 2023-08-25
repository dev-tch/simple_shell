#include "main_shell.h"
#include "strings.h"
#include "list.h"
#include "errors.h"
#include "cleanup.h"
#include "helper_functions.h"

int  read_command(char *program, char  **user_input, size_t *n);
int  add_args_cmd_to_list(char *program, char *user_input, LinkedList **head,
int status_code);
int  handle_errors(char *program, char *command);
int handle_path(char *program, char **env, char *name_cmd, LinkedList **head);
/**
 * main - entry point
 * @argc: number of arguments
 * @argv: list of arguments
 * @env: environnment variables
 * Return: (0==> ok ) (1 ==> ko)
 */
int main(int argc, char *argv[], char **env)
{
	/*local variables */
	int loop = 1;
	LinkedList *head = NULL;
	char *user_input = NULL;
	char *program = NULL;
	int read_ok = 1;
	int i = 0;
	size_t n = 0;
	char **args = NULL;
	LinkedList *list_env = NULL;
	int len_args = 0;
	char **new_env = NULL;
	LinkedList *alia_l = NULL;
	LinkedList *cmds   = NULL;
	int ret = 0, no_err = 0, path_ok = 0;
	LinkedList *temp = NULL;
	int status_code = 0;

	if (argc >= 0)
	{
		program = argv[0];
	}
	else
	{
		exit(EXIT_FAIL);
	}

	/*gloable List ==> contains environnements variables of shell*/
	conv_env_to_list(&list_env, env);
	while (loop)
	{
		if (read_ok == -1 || read_ok == -2)
		{
			if (isatty(STDIN_FILENO))
			{
				/*errno = 0;*/
				display_prompt("\n", 1);
			}
			break;
		}
		if (isatty(STDIN_FILENO))
		{
			errno = 0;
			if (!display_prompt("$ ", 2)) /*test 10*/
			{
				cleanupInput(&user_input, &n);
				cleanupList(&cmds);
				cleanupArray(list_len(list_env), &new_env);
				cleanupList(&list_env);
				cleanupList(&alia_l);
				cleanupArray(list_len(head), &args);
				cleanupList(&head);
				exit(EXIT_FAIL);
			}
		}

		cleanupInput(&user_input, &n);
		read_ok = read_command(program, &user_input, &n);
		if (!read_ok)
		{
			continue;
		}
		/*function to save multiple commands seperated with symbol (;)*/
		ret = save_commands(&cmds, user_input);
		if (cmds != NULL)
		temp = cmds;
		/*execute every command in list cmds*/
		i = 0;
		while (ret > 0 && temp != NULL)
		{
			i = add_args_cmd_to_list(program, temp->arg, &head, status_code);
			if (i > 0 && head != NULL)
			{
				new_env = list_to_array(list_env);
				proc_alias(&head, alia_l);
				/*path_ok */
				path_ok = handle_path(program, new_env, head->arg, &head);
				args = list_to_array(head);
				len_args = list_len(head);
				if (_strcmp(args[0], "exit") == 0)
				{
					cleanupInput(&user_input, &n);
					cleanupList(&head);
					cleanupList(&cmds); /*fix valgrind memory leaks */
					temp = NULL;
				}
				/*test if  builtin function of shell*/
				loop = lunch_builtin(program, len_args,  args, new_env, &list_env,
					&alia_l);
				if (loop  == NOT_BUILT_IN)
				{
					/*if (path_ok)*/ /*possible impact*/
					if (path_ok)
					{
						no_err = handle_errors(program, args[0]);
					}
					if (no_err && path_ok)
					{
						/*lunch the excution of command with process child*/
						loop = lunch_shell_execution(program, len_args, args, new_env,
						&status_code);

					}
				}
			}
			/*after each process of command*/
			/*cleanup(&user_input, &head, len_args, &args);*/
			/*cleanupInput(&user_input, &n);*/
			cleanupArray(len_args, &args);
			cleanupList(&head);
			cleanupArray(list_len(list_env), &new_env);
			if (temp != NULL)
			temp = temp->next;
			ret--;
			i = 0;
			no_err  = 0;
			path_ok = 0;
		}

		/*after finish the excution of list command */
		cleanupInput(&user_input, &n);
		cleanupList(&cmds);
	}
	/* cleanup after while */
	cleanupInput(&user_input, &n);
	cleanupList(&cmds);
	cleanupArray(list_len(list_env), &new_env);
	cleanupArray(list_len(head), &args);
	cleanupList(&head);
	cleanupList(&list_env);
	cleanupList(&alia_l);
	return (0);
}
/**
* read_command - read input from stdin
* @program: name of shell program
* @user_input: pointer to pointer char
* @n: address of variable that holds the size of input buffer
* Return: (0: next loop iteration) (-1: break loop )(1: continue task)
*/
int read_command(char *program, char **user_input, size_t *n)
{
	ssize_t nb_bytes = getline(user_input, n, stdin);
	int err_num = 0;
	size_t len = 0;

	err_num = errno;

	if (nb_bytes == -1)
	{
		if (err_num != 0 && err_num != 25)
		{
			print_error(program, err_num, STD_ERROR);
			exit(EXIT_FAIL);
		}
		else if (err_num == 0 || err_num == 25)
		{
			cleanupInput(user_input, n);
			return (-2);
		}
	}

	if (*user_input == NULL)
	{
		return (-1);
	}

	len = strlen(*user_input);
	if (len >= 1 && (*user_input)[len - 1] == '\n')
	{
		(*user_input)[len - 1] = '\0';
	}
	else
	{
		cleanupInput(user_input, n);
		return (-1);
	}

	if (len <= 1)
	{
		cleanupInput(user_input, n);
		return (0);
	}
	return (1);
}
/**
* add_args_cmd_to_list - save name commmant and its arguments in list
* @program: name of shell program
* @user_input: pointer to input entered by user
* @head: pointer to pointer to the head node of list
* @status_code: int status code exit
* Return: number of nodes added to list
*/
int add_args_cmd_to_list(char *program, char *user_input, LinkedList **head,
int status_code)
{
int i = 0, pid = 0;
char *delimiters = " \n\r\t", *token = NULL, *ptr  = NULL;
LinkedList *inserted_node = NULL;
int test = 0;
pid = getpid();
token = strtok(user_input, delimiters);
while (token != NULL)
{
	/*test if symbol of comments(#) found*/
	if (*token == '#')
		break; /*ignore the rest of command*/
	if (!is_empty(token))
	{
		/*handle the symbole $$: The process number of the current shell*/
		if (_strcmp(token, "$$") == 0 || _strcmp(token, "$?") == 0)
		{
		test = token[1] == '?';
		ptr = (test) ? conv_nb_to_str(status_code) : conv_nb_to_str(pid);
		inserted_node = add_node_end(head, ptr);
		i++;
		}
		else
		{
			inserted_node = add_node_end(head, token);
			i++;
		}
		if (inserted_node == NULL)
		{
			print_error(program, MALLOC_ERROR, NEW_ERROR);
			break;
		}
	}
	token = strtok(NULL, delimiters);
}
	return (i);
}
/**
* handle_errors - check if command is valid
* @program: name of shell program
*@command: name of command
*Return: void
*/
int handle_errors(char *program, char *command)
{
	struct stat st;
	int err = 0;

	/*check if  file exist*/
	err = stat(command, &st);
	if (err == -1)
	{
		print_error(program, errno, STD_ERROR);
		return (0);
	}

	/*check If file is excutable */
	err = access(command, X_OK);
	if (err == -1)
	{
		print_error(program, errno, STD_ERROR);
		return (0);
	}
	return (1);
}
/**
* handle_path - verify if command exist in path
* @program: initial program that lunch shell
* @env: environnment variables
* @name_cmd: command name
* @head: list contains command name and its arguments
* Return: void
*/
int  handle_path(char *program, char **env, char *name_cmd, LinkedList **head)
{
	int builtin    = 0;
	int test_path  = 0;
	char *var_path = NULL;
	LinkedList *head_path = NULL;
	int ret_del   = 1;

	/*test if command is prefixed with directory symbol*/
	if (*name_cmd == '/' || *name_cmd == '.' || *name_cmd == '~')
	return (1);
	/*test if command is builtin function*/
	builtin = is_builtin(name_cmd);
	if (builtin)
		return (1);

	test_path = convert_path_to_list(program, env, &head_path);
	if (test_path)
	{
		var_path = lookup_in_path(name_cmd, head_path);
		if (var_path == NULL && !is_empty(name_cmd))
		{
			print_err_127(program, name_cmd);
				return (0);
		}
		if (var_path != NULL)
		{
			ret_del =  delete_first_node(head);
			if (ret_del == -1)
				return (0);
			add_node_first(head, var_path);
			if (head_path != NULL)
				/*free_list(head_path);*/
				cleanupList(&head_path);
			if (var_path != NULL)
				free(var_path);
		}
		cleanupList(&head_path);
	}
	return (1);
}

