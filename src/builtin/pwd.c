#include "minishell.h"

int	cmd_pwd(char **envp, char **argv)
{
	printf("cmd pwd is called\n");
	char	*path;

	(void)argv;	
	path = ft_getenv(envp, "PWD");
	if (!path)
	{
		//에러처리
	}
	printf("%s\n", path);
	return (0);
}