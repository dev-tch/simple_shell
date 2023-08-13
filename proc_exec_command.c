#include "errors.h"
#include "list.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
/**
* lunch_shell_execution - handle process child and parrent
* @program:  name of program shell
* @h: list contains commands
* @env: environnement args
* Return: void
*/
int lunch_shell_execution(char *program, info_cmd *h, char **env)
{
pid_t id_process;
int status_process;
char **args;
id_process = fork();

if (id_process == 0)
{       args = list_to_array(h);
	if (execve(args[0], args, env) == -1)
	{
		print_error(program, errno, STD_ERROR);
		exit(EXIT_FAIL);
	}
	/*execution process children*/
}
else if (id_process < 0)
{
	/*error creation fork process */
	print_error(program, errno, STD_ERROR);
}
else
{
	do {
		waitpid(id_process, &status_process, WUNTRACED);
	} while (!WIFEXITED(status_process) && !WIFSIGNALED(status_process));
	/*execution process parent*/
}
return (1);
}
