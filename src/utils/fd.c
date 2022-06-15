#include "minishell.h"

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
