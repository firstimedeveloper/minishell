#include "minishell.h"



int	cd_rel(char **argv)
{
	(void)argv;

	return (0);
}

#define MAX 1024

int cmd_cd(char **argv)
{
	printf("cmd cd is called\n");

	char name[MAX];//
	char *old_pwd;
	char *pwd;

	old_pwd = NULL;
	pwd = NULL;
	getcwd(old_pwd, MAX);
	if (argv[1][0] == '/') //절대경로
	{
		if (chdir(argv[1]) == -1)
		{
			//에러처리
		}
	}
	else if (argv[1][0] == '.') //상대경로
	{
		cd_rel(argv);
	}
	getcwd(pwd, MAX);
	printf("After Current Directory:%s\n",getcwd(name,MAX));//
	free(pwd);
	free(old_pwd);
	return (0);
}


/*
절대 상대경로만 사용하는 cd 구현하기 
변경할 디렉토리를 지정할 때 절대 경로 이름 또는 상대 경로 이름을 사용할 수 있습니다. 절대 경로 또는 전체 경로는 시스템 루트 /에서 시작되고 상대 경로는 현재 디렉토리에서 시작됩니다.

두번째(명령어 다음으)로 오는 경로에 대해서만 반응한다.

만일 없는 디렉토리라면?           bash: cd: aa: No such file or directory
만일 디렉토리가 아니고 파일이라면?  bash: cd: aa: Not a directory >> 이건 에러 넘버 찾아서 하면 될 것 같다. 

chdir   int chdir(const char *pathname);
> - 와 ../ 를 알아서 처리한다. 
> 아 근데 둘다 부모프로세서의 경로를 토대로만 움직임 > 미니셀 안에서의 경로가 저장되어 있지 않다. 
>>> home이 어딘지 환경변수 설정을 해놔야할 것 같다. 


인자로 > 이 오면 
bash-3.2$ cd >
bash: syntax error near unexpected token `newline' // 이거 다음에는 아무일도 일어나지 않는다. 
bash-3.2$ cd > a // 이거 다음에는 home으로 간다. 



환경변수 와 ~ ?

*/