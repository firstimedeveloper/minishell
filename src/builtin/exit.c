#include "minishell.h"

int cmd_exit(char **argv)
{
	(void)argv;
	printf("cmd exit is called\n");

	return (1);
}
