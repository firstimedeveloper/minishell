#include "minishell.h"
#define MAX 1024

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
		chdir(home);
		free(home);
		return (0);
	}

	// char path[MAX];//
	// getcwd(path, MAX);//
	// printf("pwd	: %s\n", path);	//
	// printf("b2b2\n");//
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
	}
	else
		if (cd_no_argv(sh, sh->envp) == -1)
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