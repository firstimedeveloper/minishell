#include "minishell.h"
#define MAX 1024



int	cd_no_argv(void)
{
	if (chdir("$HOME") == -1)
		{
			//에러처리
		}
	char path[MAX];
	getcwd(path, MAX);
	printf("pwd	: %s\n", path);	//
	return (0);
}

int	cd_no_argv2(char **envp)
{
	char *home;

	home = ft_getenv(envp, "HOME");
	if (chdir(home) == -1)
		{
			//에러처리
		}

	char path[MAX];
	getcwd(path, MAX);
	printf("pwd	: %s\n", path);	//
	printf("b2b2\n");
	return (0);
}
//////////home을 미니쉘이 위치한 곳으로 해야하는지 아니면 본 컴퓨터의 홈디렉으로 설정해야하는지 

int cmd_cd(char **envp, char **argv)
{
	printf("cmd cd is called\n");

	char path[MAX];
//	char *old_pwd;
//	char *pwd;

	if (argv[1])
	{	
		printf("is argv\n");
		if (chdir(argv[1]) == -1)
		{
			//에러처리
		}
	}
	else
	{
		printf("no argv\n");
		if (cd_no_argv2(envp) == -1)
		{

		}
	}

	envp = ch_envp_with_name(envp, "OLDPWD=", ft_getenv(envp, "PWD"));
//	old_pwd = ft_strjoin("OLDPWD=", ft_getenv(envp, "PWD"));
//	printf("old_pwd	: %s\n", old_pwd);//
//	envp = change_envp(envp, old_pwd);	

	getcwd(path, MAX);
	envp = ch_envp_with_name(envp, "PWD=", path);
//	pwd = ft_strjoin("PWD=", path);
//	printf("pwd	: %s\n", pwd);	//
//	envp = change_envp(envp, pwd);

	int i;
	i = 0;
	while (envp[i])
	{
		printf("unset %d	:	%s\n", i, envp[i]);
		i++;
	}

//	free(pwd);
//	free(old_pwd);
	return (0);
}
