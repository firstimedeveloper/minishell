#include "minishell.h"

void	cmd_pwd(t_minishell *sh)
{
	printf("cmd pwd is called\n");
	char	*path;

	path = getcwd(NULL, 0);
 	if (path == NULL)
	{
		printf("minishell: pwd: %s", strerror(errno));
		sh->e_status = errno;
	}
	else
	{
		printf("%s\n", path);
		sh->e_status = 0;
	}
	free(path);
}