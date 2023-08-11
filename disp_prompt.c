#include "main_shell.h"
int display_prompt(char *str, int size)
{
    int ret;
    ret = isatty(STDIN_FILENO);
    if (ret == 1 )
    {
        write(STDOUT_FILENO , str, size);
    }

    return (0);
}
