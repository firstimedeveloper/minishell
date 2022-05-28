#include "minishell.h"

int	cmd_pwd(char **argv)
{
	printf("cmd pwd is called\n");
	char	*path;

	(void)argv;	
	path = (char *)getenv("PWD");
	if (!path)
	{
		//에러처리
	}
	printf("%s\n", path);
	return (0);
}


/*
getcwd
생길 수 있는 에러 사항 확인하기 
getcwd는 버퍼의 크기를 지정해야하서 getenv를 사용
*/