#include "minishell.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    //t_minishell shell;
    char        *line;

    line = NULL;
    while (1)
    {
        read_line(line);
        //parse(&shell, line);
    }

    return (0);
}