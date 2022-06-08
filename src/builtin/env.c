#include "minishell.h"

void	cmd_env(t_minishell *sh, char **argv)
{
	printf("cmd env is called\n");
	int	i;

	if (argv[1])
	{
		printf("minishell: env: minishell env don't need argv.\n");
		sh->e_status = 1;
		return ;
	}
	i = 0;
	while (sh->envp[i])
		printf("%s\n", sh->envp[i++]);
	sh->e_status = 0;
}
