#include "minishell.h"

int	cd_no_argv(t_minishell *sh, char **envp)
{
	char *home;

	home = ft_getenv(envp, "HOME");
	if (home == NULL)
	{
		printf("minishell: cd: HOME not set\n");
		sh->e_status = 1;
		free(home);
		return (1);
	}
	else
	{
		if (chdir(home) == -1)
		{
			printf("minishell: cd: %s\n", strerror(errno));
			sh->e_status = errno;
			free(home);
			return (1);		
		}
		sh->e_status = 0;
		free(home);
		return (0);
	}
}

void	cmd_cd(t_minishell *sh, char **argv)
{
	printf("cmd cd is called\n");

	char path[MAX];

	if (argv[1])
	{	
		if (chdir(argv[1]) == -1)
		{
			printf("minishell: cd: %s: No such file or directory\n", argv[1]);
			sh->e_status = 1;
			return ;
		}
		sh->e_status = 0;
	}
	else
		if (cd_no_argv(sh, sh->envp) == 1)
			return ;

	ch_envp_with_name(&(sh->envp), "OLDPWD=", ft_getenv(sh->envp, "PWD"));	
	getcwd(path, MAX);
	ch_envp_with_name(&(sh->envp), "PWD=", path);


/* 	int i;
	i = 0;
	while (sh->envp[i])
	{
		printf("unset %d	:	%s\n", i, sh->envp[i]);
		i++;
	} */
}


/*
cd에서 발생할 수 있는 에러 
No such file or directory
HOME not set
*/