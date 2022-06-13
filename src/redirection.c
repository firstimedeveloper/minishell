
#include "minishell.h"
//////exit_status

void	redirection_input(t_cmd *cmd, t_cmd *redir)
{
	char	*open_file;
	int		temp_fd;

	open_file = redir->next->content;
	temp_fd = open(open_file, O_RDONLY);
	if (temp_fd == -1)
	{
		ft_error_redir(strerror(errno), 1, cmd->redir_in);
		// printf("minishell: %s\n", strerror(errno));
		// ft_close(cmd->redir_in);
		// cmd->redir_in = -1;
		// g_e_status = 1;
		//원래 cur->argv, content. free하는 곳 찾기		
		exit(1);
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
	temp_fd = open(new_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
	{
		ft_error_redir(strerror(errno), 1, cmd->redir_out);
		// printf("minishell: %s\n", strerror(errno));
		// ft_close(cmd->redir_out);
		// cmd->redir_out = -1;
		// g_e_status = 1;
		//원래 cur->argv, content. free하는 곳 찾기
		exit(1);
	}
	if (cmd->redir_out > 0)
		ft_close(cmd->redir_out);
	cmd->redir_out = temp_fd;
	dup2(cmd->redir_out, 1);
	ft_close(cmd->redir_out);
	cmd->redir_out = -1;
}

// void	redirection_append(t_cmd *cmd, t_cmd *redir)
// {
// 	char	*new_file;
// 	int		temp_fd;

// 	new_file = redir->next->content;
// 	temp_fd = open(new_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (temp_fd == -1)
// 	{
// 		ft_error_redir(strerror(errno), 1, cmd->redir_out);

// 		// printf("minishell: %s\n", strerror(errno));
// 		// ft_close(cmd->redir_out);			이거 왜하지 아직 열질 않았는 
// 		// cmd->redir_out = -1;
// 		// g_e_status = 1;
// 		//원래 cur->argv, content. free하는 곳 찾기
// 		exit(1);
// 	}
// 	if (cmd->redir_out > 0)
// 		ft_close(cmd->redir_out);
// 	cmd->redir_out = temp_fd;
// 	dup2(cmd->redir_out, 1);
// 	ft_close(cmd->redir_out);
// 	cmd->redir_out = -1;
// }

void	redirection_append(t_cmd *cmd, t_cmd *redir)
{
	char	*new_file;

	new_file = redir->next->content;
	if (cmd->redir_out > 0)
		ft_close(cmd->redir_out);
	cmd->redir_out = open(new_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->redir_out == -1)
	{
		//ft_error_redir(strerror(errno), 1, cmd->redir_out);

		printf("minishell: %s\n", strerror(errno));
		ft_close(cmd->redir_out);			
		cmd->redir_out = -1;
		g_e_status = errno;
		//원래 cur->argv, content. free하는 곳 찾기
		exit(errno);
	}

	dup2(cmd->redir_out, 1);
	ft_close(cmd->redir_out);
	cmd->redir_out = -1;///////////////이거 ft_close 안으로 넣어도 되는지 물어보기 
}


void	redirection_heredoc(t_minishell *sh, t_cmd *cmd, t_cmd *redir)
{
	char	*end;
	char	*line;
	int		temp_fd;

	end = redir->next->content;
	temp_fd = open("heredoc_tempfile", O_WRONLY | O_CREAT | O_EXCL, 0600);
	if (temp_fd == -1)
	{
		printf("minishell: %s\n", strerror(errno));
		ft_close(temp_fd);			
		temp_fd = -1;
		g_e_status = errno;
		//원래 cur->argv, content. free하는 곳 찾기
		exit(errno);	
	}
	dup2(sh->in, 0); //키보드와 모니터로 입출력하도록 set
	dup2(sh->out, 1); // 이거는 계속 쓸거니까 닫을 필요가 없음 모두 끝나기 전에만 없애면 됨 
	while (1)	// 키보드와 모니터로 입력받기 
	{
		read_line_heredoc(&line);
		if (ft_strncmp(line, end, ft_strlen(line), ft_strlen(end)))
		{
			ft_putendl_fd(line, temp_fd);
			free(line);
		}
		else
			break;
	}
	ft_close(temp_fd);
	temp_fd = -1;

	if (cmd->redir_in > 0)
		ft_close(cmd->redir_in);
	cmd->redir_in = open("heredoc_tempfile", O_RDONLY);
	if (cmd->redir_in == -1)
	{
		printf("minishell: %s\n", strerror(errno));
		ft_close(cmd->redir_in);			
		cmd->redir_in = -1;
		g_e_status = errno;
		//원래 cur->argv, content. free하는 곳 찾기
		exit(errno);
	}
	if (cmd->is_left_pipe)
	{
		dup2(cmd->fds[1], 1);	// 다음 명령어에 들어오는 입력이 파이프를 통해도록 한다. 
		//ft_close(cmd->fds[1]);
	}
	
	dup2(cmd->redir_in, 0);	// 모니터가 아니고 이 파일으 ㅣ내용이 지금 명령어에 입력되도록 한다. 
	ft_close(cmd->redir_in);
	cmd->redir_in = -1;
	
	if (unlink("heredoc_tempfile") == -1)
		ft_error_open(strerror(errno), errno);
}

// 일단 커맨드가 가장 처음에 들어온다고 가정하고 작성
t_cmd	*redirection(t_minishell *sh, t_cmd *cmd)
{
	t_cmd	*is_redir;

	is_redir = cmd;
	// fprintf(stderr,"%s is in redirection\n", cmd->content);
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
