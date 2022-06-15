/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 03:13:37 by san               #+#    #+#             */
/*   Updated: 2022/06/14 03:13:41 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cmd_type(char *s, int is_head, int *type)
{
	if (is_head)
		*type = TYPE_CMD;
	else if (*s == '|')
		*type = TYPE_PIPE;
	else if (*s == '<')
	{
		*type = TYPE_REDIR_INPUT;
		if (*(s + 1) && *(s + 1) == '<')
			*type = TYPE_REDIR_HEREDOC;
	}
	else if (*s == '>')
	{
		*type = TYPE_REDIR_OUTPUT;
		if (*(s + 1) && *(s + 1) == '>')
			*type = TYPE_REDIR_APPEND;
	}
	else
		*type = TYPE_ARG;
}

int	init_cmd_list(t_minishell *sh, char **split)
{
	t_cmd	*cur;
	t_cmd	*tmp;
	char	*expanded_str;
	int		is_head;
	int		type;

	expanded_str = handle_expansion(sh, *split++);
	cur = ft_lstnew(expanded_str, TYPE_CMD, 1, 1);
	sh->cmd_list = cur;
	while (*split)
	{
		if (cur->type == TYPE_PIPE)
			is_head = 1;
		else
			is_head = 0;
		expanded_str = handle_expansion(sh, *split);
		handle_cmd_type(expanded_str, is_head, &type);
		tmp = ft_lstnew(expanded_str, type, is_head, 0);
		if (!tmp)
			return (1);
		ft_lstadd_back(&sh->cmd_list, tmp);
		split++;
		cur = cur->next;
	}
	return (0);
}

int	parse(t_minishell *sh, char *line)
{
	char	**split;
	t_cmd	*cur;

	(void)sh;
	while (*line == ' ')
		line++;
	if (!line || !*line)
		return (1);
	split = ft_split(line, ' ');
	if (!split || !*split)
		return (1);
	if (init_cmd_list(sh, split))
		return (1);
	cur = sh->cmd_list;
	while (cur)
		cur = cur->next;
	ft_free_all(split);
	return (0);
}
