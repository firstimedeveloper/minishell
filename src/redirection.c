
#include "minishell.h"


void	redirection_input(t_cmd **cmd, t_cmd *tmp)
{
	(void)tmp;
	(void)cmd;
}

void	redirection_output(t_cmd *cmd, t_cmd *tmp)
{
	char	*new_file;
	int		temp_fd;

	new_file = tmp->next->content;
	fprintf(stderr, "here\n");
	temp_fd = open(new_file, O_WRONLY | O_CREAT, 0644);
	if (temp_fd == -1)
	{
		fprintf(stderr, "error\n");
		ft_close(cmd->redir_out);
		cmd->redir_out = -1;
		return ;
	}
	if (cmd->redir_out > 0)
		ft_close(cmd->redir_out);
	cmd->redir_out = temp_fd;
}

void	redirection_append(t_cmd **cmd, t_cmd *tmp)
{
	(void)tmp;
	(void)cmd;
}

void	redirection_heredoc(t_cmd **cmd, t_cmd *tmp)
{
	(void)tmp;
	(void)cmd;
}

// 일단 커맨드가 가장 처음에 들어온다고 가정하고 작성
t_cmd	*redirection(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == TYPE_REDIR_INPUT)
			redirection_input(&cmd, tmp);
		else if (tmp->type == TYPE_REDIR_OUTPUT)
			redirection_output(cmd, tmp);
		else if (tmp->type == TYPE_REDIR_APPEND)
			redirection_append(&cmd, tmp);
		else if (tmp->type == TYPE_REDIR_HEREDOC)
			redirection_heredoc(&cmd, tmp);
		tmp = tmp->next;
	}

	return (cmd);
}
