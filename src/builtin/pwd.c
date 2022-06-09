#include "minishell.h"

void	cmd_pwd(void)
{
	printf("cmd pwd is called\n");
	char	*path;

	path = getcwd(NULL, 0);
 	if (path == NULL)
	{
		printf("minishell: pwd: %s\n", strerror(errno));
		g_e_status = errno;
	}
	else
	{
		printf("%s\n", path);
		g_e_status = 0;
	}
	free(path);
}