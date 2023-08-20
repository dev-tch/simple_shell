#include "new_types.h"
#include <stdio.h>
#include <strings.h>
#include "common.h"
#include "list.h"

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

	(void)alia_l;
	(void)prg;

	env     = (env == NULL) ? NULL : env;
	env_l   = (env == NULL) ? NULL : env_l;

	printf("%d\n", la);
	if (la == 2)
	{
		printf("%s\n", args[1]);
		printf("imhere");
		/*we have to print aliases*/
		add_node_end(alia_l, args[1]);
		print_list(*alia_l);
	}

	return (1);
}


