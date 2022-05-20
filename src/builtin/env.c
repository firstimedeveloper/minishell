#include "minishell.h"

int	cmd_env(char **envp)
{
	printf("cmd env is called\n");
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
