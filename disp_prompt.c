#include "main_shell.h"
/**
* display_prompt - show prompt is stdin
* @str: text that will be displayed to user
* @size: length of text
* Return: (0:fail)(1:done)
*/
int display_prompt(char *str, int size)
{
	int ret = 0;

	ret = isatty(STDOUT_FILENO);

	if (ret == 1)
	{
		write(STDOUT_FILENO, str, size);
	}

return (ret);
}
