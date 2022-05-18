#include "minishell.h"

int cmd_pwd(char **argv)
{
	printf("cmd pwd is called\n");
	char	path[1024];

	(void)argv;	
	if(getcwd(path, 1024) == NULL) 
	{
		//에러처리		return (1);
	}
	printf("%s\n", path);
	return (0);
}


/*
getcwd

생길 수 있는 에러 사항 확인하기 
*/