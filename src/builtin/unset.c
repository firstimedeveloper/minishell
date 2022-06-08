#include "minishell.h"

int	unset_del(char ***envp, char *str)
{
	int	i;
	int	j;
	char	**new;

	i = ft_envplen(*envp) - 1;	//new의 개수
	j = i;					//envp 값이 들어있는 마지막 인덱스
	new = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new)
		exit (1);
	new[i] = NULL;
	while (--i > -1)
	{
		if (ch_strncmp(str, get_envp_name((*envp)[j]), ft_strlen(get_envp_name((*envp)[j]))) == 0)
			j--;
		new[i] = ft_strdup((*envp)[j]);
		j--;
	}
	ft_free_double(*envp);
	*envp = new;
	return (0);	
}

void	cmd_unset(t_minishell *sh, char **argv)
{
	printf("cmd unset is called\n");

	int	i;

	i = 0;
	sh->e_status = 0;
	while (argv[++i])
	{
		if (check_argv_name(sh, argv[i], argv[0]) == 0)
		{
			if (ft_strchr(argv[i], '=') == NULL)
				unset_del(&(sh->envp), argv[i]);
			else
			{
				printf("minishell: unset: `%s': not a valid identifier\n", argv[i]);
				sh->e_status = 1;
			}
		}
	}
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

$AA 와 AA를 다르게 인식한다. 

*/

/* 
[ exit_status ]

없는 변수를 unset -> 0

인자에 숫자, 알파벳이 아닌 문자가 들어가면  -> 1

인자가 숫자로 시작하면 -> 1

오류가 있는 인자가 하나라도 들어오면 -> 1

 */