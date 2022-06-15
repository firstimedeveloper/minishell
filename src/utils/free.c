/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:15:36 by juhan             #+#    #+#             */
/*   Updated: 2022/06/15 18:15:41 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_double(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
	{
		if (ptr[i])
			free(ptr[i]);
	}
	free(ptr);
}

void	ft_exit(int exit_code)
{
	ft_error_open("malloc error", exit_code);
	exit(exit_code);
}

void	ft_free(char *str)
{
	if (str)
		free(str);
}

void	ft_free_cmd_lst(t_minishell *sh)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = sh->cmd_list;
	while (cur)
	{
		next = cur->next;
		fprintf(stderr, "program:\tfreeing %s\n", cur->content);
		free(cur->content);
		if (cur->argv)
			free(cur->argv);
		free(cur);
		cur = next;
	}
	sh->cmd_list = NULL;
}
