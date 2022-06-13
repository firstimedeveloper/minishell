/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:15:41 by san               #+#    #+#             */
/*   Updated: 2022/06/14 04:05:19 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_add(char ***envp, char *str)
{
	int		i;
	char	**new;

	i = ft_envplen(*envp) + 1;
	new = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (1);
	new[i] = NULL;
	new[--i] = ft_strdup(str);
	while (--i > -1)
		new[i] = ft_strdup((*envp)[i]);
	i = -1;
	while ((*envp)[++i])
	{
		if ((*envp)[i])
			free((*envp)[i]);
	}
	free((*envp));
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
	char	**tmp_envp;
	char	**tmp;

	tmp_envp = copy_envp(envp);
	tmp = sort_envp(tmp_envp);
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
			continue ;
		}
		printf("=\"");
		while ((*tmp)[++i])
			printf("%c", (*tmp)[i]);
		printf("\"\n");
		tmp++;
	}
	ft_free_all(tmp_envp);
}

void	cmd_export(t_minishell *sh, char **av)
{
	int		i;

	i = 0;
	g_e_status = 0;
	if (!av[1])
		export_print(sh->envp);
	else
	{
		if (ft_strncmp(av[i], "_", ft_strlen(av[i]), 1) == 0)
			return ;
		while (av[++i])
		{
			if (check_argv_name(av[i], av[0]) != 0)
				continue ;
			if (ft_getenv(sh->envp, get_envp_name(av[i])))
			{
				if (av_have_eq(av[i]))
					change_envp(&(sh->envp), av[i]);
			}
			else
				export_add(&(sh->envp), av[i]);
		}
	}
}
