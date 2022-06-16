/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:22:39 by san               #+#    #+#             */
/*   Updated: 2022/06/16 14:22:43 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *content)
{
	int				i;
	const char		*builtin[BUILTIN_COUNT] = {"cd", "echo", "env",
		"exit", "export", "pwd", "unset"};
	const size_t	builtin_len[BUILTIN_COUNT] = {2, 4, 3, 4, 6, 3, 5};

	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (!ft_strncmp(builtin[i], content, ft_strlen(content),
				builtin_len[i]))
			return (i + 1);
		i++;
	}
	return (0);
}

char	*find_is_right_path(char **paths, char *command, struct stat s)
{
	char		**paths_cpy;
	char		*path;

	paths_cpy = paths;
	while (*paths)
	{
		path = ft_strdirjoin(*paths, command);
		paths++;
		if (stat(path, &s) == 0)
		{
			ft_free_all(paths_cpy);
			return (path);
		}
		free(path);
	}
	ft_free_all(paths_cpy);
	return (NULL);
}

char	*find_path(char **envp, char *command)
{
	struct stat	s;
	char		**paths;
	char		*path;

	if (stat(command, &s) == 0)
		return (ft_strdup(command));
	path = ft_getenv(envp, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	free(path);
	return (find_is_right_path(paths, command, s));
}

void	handle_cmd_set_pipe(t_cmd *cur, int *prev_fds)
{
	if (cur->is_left_pipe)
	{
		prev_fds[0] = cur->fds[0];
		prev_fds[1] = cur->fds[1];
	}
	else if (!cur->is_left_pipe)
	{
		ft_close(cur->fds[0]);
		ft_close(cur->fds[1]);
		ft_reset_fd(cur->fds);
	}
}

int	handle_cmd(t_minishell *sh)
{
	t_cmd	*cur;
	int		prev_fds[2];

	ft_reset_fd(prev_fds);
	cur = sh->cmd_list;
	while (cur)
	{
		if (cur->type == TYPE_CMD)
		{
			init_argv(sh, cur);
			excecute_cmd(sh, cur, prev_fds, cur->path);
			handle_cmd_set_pipe(cur, prev_fds);
			if (!is_builtin(cur->content))
				ft_free(cur->path);
		}
		cur = cur->next;
	}
	return (0);
}
