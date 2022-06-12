#include "minishell.h"

int	export_add(char ***envp, char *str)	//세로줄을 하나 늘린 배열을 할당해서 복사하고 추가한다음에 새로 할당한 배열을 가리키도록 할 것
{
	int	i;
	char	**new;

	i = ft_envplen(*envp) + 1;
	new = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (1);
	new[i] = NULL;
	new[--i] = ft_strdup(str);
	while (--i > -1)
		new[i] = ft_strdup((*envp)[i]);
	ft_free_double(*envp);
	*envp = new;
	return (0);
}

char	**sort_envp(char **envp)
{
	char	*temp;
	int		i;
	int		j;

	i = ft_envplen(envp);
	while (envp[--i])
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
	int		i;

	while (*envp)
	{
		i = 0;
		printf("declare -x ");
		while ((*envp)[i] && (*envp)[i] != '=')
			printf("%c", (*envp)[i++]);
		if ((*envp)[i] == '\0')
		{
			printf("\n");
			envp++;
			continue;
		}
		printf("=\"");
		while ((*envp)[++i])
			printf("%c", (*envp)[i]);
		printf("\"\n");
		envp++;
	}
////////////아래서 세번째 행은 bash shell에서 출력되지 않음 뭔지 확인하고 출력할지말지 결정하기
}


void	cmd_export(t_minishell *sh, char **av)
{
	int i;

	i = 0;
	g_e_status = 0;
	if (!av[1])	// 인자가 없으면 환경변수 출력
		export_print(sort_envp(copy_envp(sh->envp)));
	else	// 인자 있으면 환경변수 추가, 수정
	{
		if (ft_strncmp(av[i], "_", ft_strlen(av[i]), 1))
			return ;
		while (av[++i])
		{
			if (check_argv_name(av[i], av[0]) != 0)	//환경변수 이름에 문제 있는 인자는 넘어가기
				continue;
			if (ft_getenv(sh->envp, get_envp_name(av[i])))
			{
				if (av_have_eq(av[i]))	// 환경변수 목록에 있는데 인자로 들어온 문자열에 = 가 있으면 change 한다.
					change_envp(&(sh->envp), av[i]);
			}
			else
				export_add(&(sh->envp), av[i]);
		}
	}
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


////// export TEST='testing' 이런 경우 구현해야한다.

