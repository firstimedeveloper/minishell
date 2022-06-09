#include "minishell.h"

int ft_execute()
{
	int fd[2];

	if (pipe(fd) == -1)
	{
		//에러처리 파이프 오류
	}
	return 0;
}

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	ft_reset_fd(int *fd)
{
	fd[0] = -1;
	fd[1] = -1;
}
/*

void	reset_std(t_minishell *sh)
{
	dup2(sh->in, STDIN);
	dup2(sh->out, STDOUT);
}

void	close_fds(t_minishell *sh)
{
	ft_close(sh->fdin);
	ft_close(sh->fdout);
	ft_close(sh->pipin);
	ft_close(sh->pipout);
}

void	reset_fds(t_minishell *sh)
{
	sh->fdin = -1;
	sh->fdout = -1;
	sh->pipin = -1;
	sh->pipout = -1;
	sh->pid = -1;
}
*/
