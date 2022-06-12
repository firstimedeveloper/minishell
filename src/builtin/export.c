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
	char	**tmp;

	tmp = copy_envp(envp);
	tmp = sort_envp(tmp);
	while (*tmp)
	{
		i = 0;
		printf("declare -x ");
		while ((*tmp)[i] && (*tmp)[i] != '=')
			printf("%c", (*tmp)[i++]);
		if ((*tmp)[i] == '\0')
		{
			printf("\n");
			tmp++;
			continue;
		}
		printf("=\"");
		while ((*tmp)[++i])
			printf("%c", (*tmp)[i]);
		printf("\"\n");
		tmp++;
	}
	//free(tmp);
}


void	cmd_export(t_minishell *sh, char **av)
{
	int i;

	i = 0;
	g_e_status = 0;
	if (!av[1])
		export_print(sh->envp);
//		export_print(sort_envp(copy_envp(sh->envp)));
	else
	{
		if (ft_strncmp(av[i], "_", ft_strlen(av[i]), 1) == 0)
			return ;
		while (av[++i])
		{
			if (check_argv_name(av[i], av[0]) != 0)
				continue;
			if (ft_getenv(sh->envp, get_envp_name(av[i])))////////////여기 ft_getenv어떻게 free
			{
				if (av_have_eq(av[i]))
					change_envp(&(sh->envp), av[i]);
			}
			else
				export_add(&(sh->envp), av[i]);
		}
	}
}