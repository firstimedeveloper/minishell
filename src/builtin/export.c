
#include "minishell.h"




char	**sort_envp(char **envp)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		while (++j < i)
		{
			if (ch_strncmp(envp[j], envp[j + 1], ft_strlen(envp[j])) > 0)
			{
				temp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = temp;
			}
		}
	}
	return (envp);
}


void	export_print(char **envp)
{
	char	**envp_tmp;
	int		i;


	envp_tmp = copy_envp(envp);
	envp_tmp = sort_envp(envp_tmp);
	printf("print\n");	//we can print until here

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}

//	printf("%s\n", *envp_tmp);
	while (*envp_tmp)
	{
		i = -1;
		printf("declare -x ");
		while (*envp_tmp[++i] != '=')
			printf("%c", *envp_tmp[i]);
		printf("\"");
		while (*envp[++i])
			printf("%c", *envp_tmp[i]);
		printf("\"\n");
		envp_tmp++;
	}
	free(envp_tmp);
}

int	cmd_export(t_minishell *sh, char **argv)
{
	//char	**new_env;
	printf("cmd export is called\n");

	if (!argv[1])	// 인자가 없으면 환경변수 출력
	{
		printf("hi\n");
		export_print(sh->envp);
	}
	else	// 인자 있으면 환경변수 추가, 수정
	{
		printf("nono\n");
	}
	return (0);
}


/*
export : 환경변수 추가, 수정

bash-3.2$ export WATER="a"
WATER=a

bash-3.2$ export WATER=bb
WATER=bb

bash-3.2$ export WATER = bb
bash: export: `=': not a valid identifier

bash-3.2$ export WATER =bb
bash: export: `=bb': not a valid identifier

bash-3.2$ export WATER= bb
WATER=

bash-3.2$ export WATER=bb aa //aa도 환경변수로 등록은 됨 env로 나오진 않음 
WATER=bb

bash-3.2$ export hello
내 노트북에서는 이렇게 작성하면 환경변수는 설정되는데 env로 했을때 출력되지는 않음 

bash-3.2$ export WATER==aa
WATER==aa
>>>>처음 등호빼고 그 후로 다 값 

bash-3.2$ export
이렇게하면 환경변수의 목록을 출력  
ex) 
declare -x aa
declare -x bb
declare -x hello
declare -x WATER="======aa"

bash-3.2$ export WATER====aa cc=b
WATER====aa
cc=b
*/