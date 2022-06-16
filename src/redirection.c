/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:05:07 by san               #+#    #+#             */
/*   Updated: 2022/06/16 15:05:13 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection_input(t_cmd *cmd, t_cmd *redir)
{
	char	*open_file;
	int		temp_fd;

	open_file = redir->next->content;
	temp_fd = open(open_file, O_RDONLY);
	if (temp_fd == -1)
	{
		ft_error_redir(strerror(errno), errno, cmd->redir_in);
		exit(1);
	}
	if (cmd->redir_in > 0)
		ft_close(cmd->redir_in);
	if (!is_builtin(cmd->content))
	{
		cmd->redir_in = temp_fd;
		dup2(cmd->redir_in, 0);
		ft_close(cmd->redir_in);
	}
	cmd->redir_in = -1;
}

void	redirection_output(t_cmd *cmd, t_cmd *redir)
{
	char	*new_file;
	int		temp_fd;

	new_file = redir->next->content;
	temp_fd = open(new_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		ft_error_redir(strerror(errno), errno, temp_fd);
		exit(1);
	}
	if (cmd->redir_out > 0)
		ft_close(cmd->redir_out);
	cmd->redir_out = temp_fd;
	dup2(cmd->redir_out, 1);
	ft_close(cmd->redir_out);
	cmd->redir_out = -1;
}

void	redirection_append(t_cmd *cmd, t_cmd *redir)
{
	char	*new_file;

	new_file = redir->next->content;
	if (cmd->redir_out > 0)
		ft_close(cmd->redir_out);
	cmd->redir_out = open(new_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->redir_out == -1)
	{
		ft_error_redir(strerror(errno), errno, cmd->redir_out);
		exit(1);
	}
	dup2(cmd->redir_out, 1);
	ft_close(cmd->redir_out);
	cmd->redir_out = -1;
}

void	redirection_heredoc(t_minishell *sh, t_cmd *cmd, t_cmd *redir)
{
	char		*end;
	int			temp_fd;
	struct stat	s;

	if (stat("heredoc_tempfile", &s) == 0)
		unlink("heredoc_tempfile");
	end = redir->next->content;
	open_for_heredoc(sh, cmd, end);
	if (cmd->is_left_pipe)
		dup2(cmd->fds[1], 1);
	if (!is_builtin(cmd->content))
	{
		dup2(cmd->redir_in, 0);
		ft_close(cmd->redir_in);
	}
	cmd->redir_in = -1;
	temp_fd = unlink("heredoc_tempfile");
	if (temp_fd == -1)
		ft_error_redir(strerror(errno), errno, temp_fd);
}

t_cmd	*redirection(t_minishell *sh, t_cmd *cmd)
{
	t_cmd	*is_redir;

	is_redir = cmd;
	while (is_redir)
	{
		if (is_redir->type == TYPE_PIPE)
			break ;
		if (is_redir->type == TYPE_REDIR_INPUT)
			redirection_input(cmd, is_redir);
		else if (is_redir->type == TYPE_REDIR_OUTPUT)
			redirection_output(cmd, is_redir);
		else if (is_redir->type == TYPE_REDIR_APPEND)
			redirection_append(cmd, is_redir);
		else if (is_redir->type == TYPE_REDIR_HEREDOC)
			redirection_heredoc(sh, cmd, is_redir);
		is_redir = is_redir->next;
	}
	return (cmd);
}
