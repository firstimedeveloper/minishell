#include "minishell.h"

int	cmd_exit(char **argv)
{
	(void)argv;
	printf("cmd exit is called\n");

	printf("exit\n");
	exit(0);
	return (0);
}
