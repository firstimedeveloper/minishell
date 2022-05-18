#include "minishell.h"

int cmd_exit(t_cmd *cmd)
{
	(void)cmd;
	printf("cmd exit is called\n");

	return (1);
}
