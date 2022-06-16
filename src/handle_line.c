/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:50:12 by san               #+#    #+#             */
/*   Updated: 2022/06/16 16:50:14 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_line(char **line_read)
{
	if (*line_read)
	{
		free(*line_read);
		*line_read = (char *) NULL;
	}
	*line_read = readline("minishell> ");
	if (*line_read && **line_read)
		add_history(*line_read);
	else if (*line_read == NULL)
	{
		printf("\033[1A");
		printf("\033[11C");
		printf("exit\n");
		free(*line_read);
		exit(127);
	}
}

void	read_line_heredoc(char **line_read)
{
	*line_read = readline("> ");
	if (*line_read == NULL)
	{
		free(*line_read);
		exit(0);
	}
}

void	read_line_heredoc_continue(char *end, int temp_fd)
{
	char	*line;

	while (1)
	{
		read_line_heredoc(&line);
		if (ft_strncmp(line, end, ft_strlen(line), ft_strlen(end)))
		{
			ft_putendl_fd(line, temp_fd);
			free(line);
		}
		else
			break ;
	}	
}

void	open_for_heredoc(t_minishell *sh, t_cmd *cmd, char *end)
{
	int		temp_fd;

	temp_fd = open("heredoc_tempfile", O_WRONLY | O_CREAT | O_EXCL, 0600);
	if (temp_fd == -1)
	{
		ft_error_redir(strerror(errno), errno, cmd->redir_out);
		exit(1);
	}
	dup2(sh->in, 0);
	dup2(sh->out, 1);
	read_line_heredoc_continue(end, temp_fd);
	ft_close(temp_fd);
	temp_fd = -1;
	if (cmd->redir_in > 0)
		ft_close(cmd->redir_in);
	cmd->redir_in = open("heredoc_tempfile", O_RDONLY);
	if (cmd->redir_in == -1)
	{
		ft_err_hdoc(strerror(errno), errno, cmd->redir_in, "heredoc_tempfile");
		exit(errno);
	}
}
