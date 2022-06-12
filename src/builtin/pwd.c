#include "minishell.h"

void	cmd_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
 	if (path == NULL)
		ft_error("pwd", NULL, strerror(errno), errno);
	else
	{
		printf("%s\n", path);
		g_e_status = 0;
	}
	free(path);
}