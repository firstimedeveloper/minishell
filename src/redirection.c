
#include "minishell.h"
//////exit_status

void	redirection_input(t_cmd *cmd, t_cmd *redir)
{
	char	*open_file;
	int		temp_fd;

	open_file = redir->next->content;
	temp_fd = open(open_file, O_RDONLY);
//	printf("input_fd : %d\n", temp_fd);
//	do re
	if (temp_fd == -1)
	{
		fprintf(stderr, "error\n");
		ft_close(cmd->redir_in);
		cmd->redir_in = -1;
		exit(0);
	}
	if (cmd->redir_in > 0)
		ft_close(cmd->redir_in);
	cmd->redir_in = temp_fd;
	dup2(cmd->redir_in, 0);
	ft_close(cmd->redir_in);
	cmd->redir_in = -1;

}

void	redirection_output(t_cmd *cmd, t_cmd *redir)
{
	char	*new_file;
	int		temp_fd;

	new_file = redir->next->content;
	fprintf(stderr, "redir_output_here\n");
	temp_fd = open(new_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	dup2(cmd->redir_out, 1);
	ft_close(cmd->redir_out);
	cmd->redir_out = -1;
}

void	redirection_append(t_cmd *cmd, t_cmd *redir)
{
	char	*new_file;
	int		temp_fd;

	new_file = redir->next->content;
	fprintf(stderr, "here\n");
	temp_fd = open(new_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
	dup2(cmd->redir_out, 1);
	ft_close(cmd->redir_out);
	cmd->redir_out = -1;
}

void	redirection_heredoc(t_cmd *cmd, t_cmd *redir)
{
	char	*end;
	char	*line;

	end = redir->next->content;
	if (cmd->redir_in > 0)
		ft_close(cmd->redir_in);
	dup2(STDIN, 0);
	while (1)
	{
		read_line_heredoc(&line);
		if (ft_strncmp(line, end, ft_strlen(line), ft_strlen(end)))
			ft_putendl_fd(line, 0);
		else
		{
			//들어온 입력 출력하도록 실행하도록 해야함
			printf("its end word\n");
			exit(0);
		}


	}


}

// 일단 커맨드가 가장 처음에 들어온다고 가정하고 작성
t_cmd	*redirection(t_cmd *cmd)
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
			redirection_heredoc(cmd, is_redir);
		is_redir = is_redir->next;
	}
	return (cmd);
}
