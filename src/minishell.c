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
		if (parse(&sh, line) == 1)
			continue ;
		handle_cmd(&sh);
    }

    return (0);
}
