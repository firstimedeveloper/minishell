#include "minishell.h"

int	cd_no_argv(char **envp)
{
	char *home;

	home = ft_getenv(envp, "HOME");
	if (home == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		g_e_status = 1;
		free(home);
		return (1);
	}
	else
	{
		if (chdir(home) == -1)
		{
			printf("minishell: cd: %s\n", strerror(errno));
			g_e_status = errno;
			free(home);
			return (1);
		}
		g_e_status = 0;
		free(home);
		return (0);
	}
}

void	cmd_cd(t_minishell *sh, char **argv)
{
	char path[MAX];

	if (argv[1])
	{
		if (chdir(argv[1]) == -1)
		{
			ft_error(argv[0], argv[1], strerror(errno), 1);
			return ;
		}
		g_e_status = 0;
	}
	else
		if (cd_no_argv(sh->envp) == 1)
			return ;
	ch_envp_with_name(&(sh->envp), "OLDPWD=", ft_getenv(sh->envp, "PWD"));
	getcwd(path, MAX);
	ch_envp_with_name(&(sh->envp), "PWD=", path);
}