/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:26:23 by san               #+#    #+#             */
/*   Updated: 2022/06/14 02:26:43 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_del(char ***envp, char *str)
{
	int		i;
	int		j;
	char	**new;

	i = ft_envplen(*envp) - 1;
	j = i;
	new = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new)
		exit (1);
	new[i] = NULL;
	while (--i > -1)
	{
		if (ch_strncmp(str, get_envp_name((*envp)[j]),
			ft_strlen(get_envp_name((*envp)[j]))) == 0)
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
