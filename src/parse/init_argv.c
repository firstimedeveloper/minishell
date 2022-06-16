/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 03:13:24 by san               #+#    #+#             */
/*   Updated: 2022/06/16 13:10:53 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_argv(t_cmd *cmd, int len)
{
	char	**argv;
	int		i;

	argv = malloc(sizeof(char *) * (len + 1));
	if (!argv)
		ft_exit(ERR_MALLOC);
	argv[0] = cmd->content;
	argv[len] = 0;
	i = 1;
	while (i < len)
	{
		if (cmd->type == TYPE_ARG && cmd->prev->type <= TYPE_ARG)
		{
			argv[i] = cmd->content;
			if (!argv[i])
			{
				ft_free_all(argv);
				ft_exit(ERR_MALLOC);
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (argv);
}

//양옆에 파이프가 있는지 확인하고 이 커멘드 뒤로의 argv 개수를 센다 . 
void	get_arg_count(t_cmd *cmd)
{
	t_cmd	*next;

	next = cmd;
	cmd->arg_count = 1;
	while (next)
	{
		if (next->type == TYPE_PIPE)
		{
			cmd->is_left_pipe = 1;
			next = next->next;
			if (next)
				next->is_right_pipe = 1;
			break ;
		}
		if (next->type == TYPE_ARG && next->prev->type <= TYPE_ARG)
			cmd->arg_count++;
		next = next->next;
	}
}

void	init_argv(t_minishell *sh, t_cmd *cur)
{
	// fprintf(stderr, "program:\thello\n");
	if (!is_builtin(cur->content))
		cur->path = find_path(sh->envp, cur->content);	// 명령어의 위치를 찾고

	if (cur->path != NULL || is_builtin(cur->content))				//없으면 에러 메세지 ////////////////빌트인일 떄는? 이거 꼭 있어야  하는 코드인지 
	{
		get_arg_count(cur);
		cur->argv = create_argv(cur, cur->arg_count);
		if (!cur->argv)
			ft_exit(ERR_MALLOC);
	}
}
