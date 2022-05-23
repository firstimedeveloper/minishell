#include "minishell.h"
#define MAX 1024

int	cmd_pwd(char **argv)
{
	printf("cmd pwd is called\n");
	char	*path;

	(void)argv;	
	path = NULL; //
//	if(getcwd(path, MAX) == NULL) 
	{
		//에러처리		return (1);
	}
	 getcwd(path, MAX);
	printf("%s\n", path);
	printf("%s\n", path);
	free (path);
	return (0);
}


/*
getcwd

생길 수 있는 에러 사항 확인하기 
*/