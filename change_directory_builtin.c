#include "new_types.h"

int change_dir(char *prg, int la, char  **args, char **env,
LinkedList **env_l, LinkedList **alia_l)
{
	/*unused parameters*/
	(void)prg;
	la = (la == 0) ? 0 : la;
	(void) args;
	(void) env;
	(void)env_l;
	(void)alia_l;

	return (1);
}
