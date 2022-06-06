#include "minishell.h"

int	cmd_env(char **envp, char **argv)
{
	printf("cmd env is called\n");
	int	i;

	if (argv[1])
	{
		printf("there is too many argument\n");
		return(1);
		//에러처리
	}
	i = 0;
	while (envp[i])
		printf("%s\n", envp[i++]);
	return (0);
}
