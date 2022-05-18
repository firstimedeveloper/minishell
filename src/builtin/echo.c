#include "minishell.h"

int cmd_echo(t_cmd *cmd)
{
	(void)cmd;
	printf("cmd echo is called\n");

	return (1);
}
