#include "errors.h"
#include "list.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
/**
* lunch_shell_execution - handle process child and parrent
* @prg:  name of program shell
* @len_args: number of arguments of command
* @args: arguments of command
* @env: environnement args
* Return: void
*/
int lunch_shell_execution(char *prg, int len_args, char **args, char **env)
{
	pid_t id_process;
	int status_process;
	/*len_args unused */
	len_args = (len_args == 0 ? 0 : len_args);

id_process = fork();

if (id_process == 0)
{

	if (execve(args[0], args, env) == -1)
	{
		print_error(prg, errno, STD_ERROR);
		exit(EXIT_FAIL);
	}
	/*execution process children*/
}
else if (id_process < 0)
{
	/*error creation fork process */
	print_error(prg, errno, STD_ERROR);
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
