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
		if (*line)
		{
			printf("==parsing line==\n");
			parse(&sh, line);
			printf("\n==handling cmd==\n");
			handle_cmd(&sh);
		}
    }

    return (0);
}
