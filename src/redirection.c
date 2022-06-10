
#include "minishell.h"


void	redirection_input(t_cmd **cmd, t_cmd *tmp)
{
	(void)tmp;
	(void)cmd;
}

void	redirection_output(t_cmd **cmd, t_cmd *tmp)
{
	char	*new_file;

	new_file = tmp->next->content;
	printf("here\n");
	(*cmd)->redir_out = open(new_file, O_WRONLY | O_CREAT, 0644);
	if ((*cmd)->redir_in == -1)
	{
		printf("error\n");
		//open 에러 
	}
	dup2((*cmd)->redir_out, STDOUT);
	close((*cmd)->redir_out);


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
			redirection_output(&cmd, tmp);
		else if (tmp->type == TYPE_REDIR_APPEND)
			redirection_append(&cmd, tmp);
		else if (tmp->type == TYPE_REDIR_HEREDOC)
			redirection_heredoc(&cmd, tmp);
		tmp = tmp->next;
	}

	return (cmd);
}
