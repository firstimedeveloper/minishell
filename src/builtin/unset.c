/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:26:23 by san               #+#    #+#             */
/*   Updated: 2022/06/14 03:09:09 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_del(char ***envp, char *str)
{
	int		i;
	int		j;
	char	**new;
	char	*temp;

	i = ft_envplen(*envp) - 1;
	j = i;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		ft_exit(1);
	new[i] = NULL;
	while (--i > -1)
	{
		temp = get_envp_name((*envp)[j]);
		if (ch_strncmp(str, temp,
				ft_strlen(temp)) == 0)
			j--;
		new[i] = ft_strdup((*envp)[j]);
		j--;
		free(temp);
	}
	ft_free_double(*envp);
	*envp = new;
	return (0);
}

void	cmd_unset(t_minishell *sh, char **argv)
{
	int	i;

	i = 0;
	g_e_status = 0;
	while (argv[++i])
	{
		if (check_argv_name(argv[i], argv[0]) == 0)
		{
			if (ft_strchr(argv[i], '=') == NULL)
				unset_del(&(sh->envp), argv[i]);
			else
				ft_error_2(argv[0], argv[i], 1);
		}
	}
}
