/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:13:21 by san               #+#    #+#             */
/*   Updated: 2022/06/14 02:13:33 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_env(t_minishell *sh, char **argv)
{
	int	i;

	if (argv[1])
	{
		ft_error(argv[0], argv[1], "No such file or directory", 127);
		return ;
	}
	i = -1;
	while (sh->envp[++i])
	{
		if (ft_strchr(sh->envp[i], '='))
			printf("%s\n", sh->envp[i]);
	}
	g_e_status = 0;
}
