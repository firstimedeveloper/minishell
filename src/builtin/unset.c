#include "minishell.h"

int	cmd_unset(char **envp, char **argv)
{
	(void)argv;
	(void)envp;
	printf("cmd unset is called\n");

	return (1);
}
