#include "minishell.h"

void	cmd_env(t_minishell *sh, char **argv)
{
	printf("cmd env is called\n");
	int	i;

	if (argv[1])
	{
		printf("env: %s:  No such file or directory.\n", argv[1]);
		g_e_status = 127;
		return ;
	}
	i = -1;
	while (sh->envp[++i])
	{
		if (ft_strchr(sh->envp[i], '='))
			printf("%s\n", sh->envp[i]);
	}
	g_e_status = 0;
}
