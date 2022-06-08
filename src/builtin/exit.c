#include "minishell.h"

void	cmd_exit(char **argv)
{
	printf("cmd exit is called\n");

	printf("exit\n");
	if (argv[1])
	{
		printf("minishell: exit: %s: numeric argument required\n", argv[1]);
		exit(255);
	}
	else
		exit(0);
	return (0);
}
