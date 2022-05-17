#include "minishell.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    t_minishell sh;
	(void)sh;
    char        *line;

    line = NULL;
    while (1)
    {
        read_line(&line);
		//printf("%s", line);
        parse(&sh, line);
    }

    return (0);
}
