/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:15:36 by juhan             #+#    #+#             */
/*   Updated: 2022/06/16 13:08:14 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_lstlast(t_cmd *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_cmd	*ft_lstnew(void *content, int type, int is_head, int is_first)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		exit(errno);
	ret->content = content;
	ret->arg_count = 0;
	ret->argv = NULL;
	ret->path = NULL;
	ret->type = type;
	ret->is_head = is_head;
	ret->is_left_pipe = 0;
	ret->is_right_pipe = 0;
	ret->is_first = is_first;
	ret->next = 0;
	ret->prev = 0;
	ret->redir_in = -1;
	ret->redir_out = -1;
	return (ret);
}

int	ft_lstsize(t_cmd *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
