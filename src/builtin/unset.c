#include "minishell.h"

char	**unset_del(char **envp, char *str)
{
	int	i;
	int	j;
	char	**new;

	i = ft_envplen(envp) - 1;	//new의 개수
	j = i;					//envp 값이 들어있는 마지막 인덱스
	new = malloc(sizeof(char *) * (i + 1));
//	if (!new)
//		return (1);
	new[i] = NULL;
	while (--i > -1)
	{
		if (ch_strncmp(str, get_envp_name(envp[j]), ft_strlen(get_envp_name(envp[j]))) == 0)
			j--;
		new[i] = ft_strdup(envp[j]);
		j--;
	}
	ft_free_double(envp);
	return (new);	
}

int	cmd_unset(char **envp, char **argv)
{
	printf("cmd unset is called\n");

	int	i;

	i = 0;
	while (argv[++i])
	{
		if (check_argv(argv[i]) == 0 && ft_strchr(argv[i], '=') == NULL)	//오류있는 인자는 넘어가기
			envp = unset_del(envp, argv[i]);
	}

	i = 0;
	while (argv[i])
	{
		printf("unset %d	:	%s\n", i, envp[i]);
		i++;
	}

	return (0);
}


/*
리눅스 변수 제거 unset

bash-3.2$ unset AA=a
bash: unset: `AA=a': not a valid identifier

bash-3.2$ unset =
bash: unset: `=': not a valid identifier
bash-3.2$ unset [
bash: unset: `[': not a valid identifier
bash-3.2$ unset 1
bash: unset: `1': not a valid identifier

없는 변수를 넣어도 그냥 반응하지 않는다. 

인자를 여러개 넣을 수 있다. 

*/