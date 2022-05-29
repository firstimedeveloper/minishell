#include "minishell.h"


/*
int	cd_rel(char **argv)
{
	(void)argv;
//지금 경로를 따온다음에 뒤에있는 /한칸을 지워서 반환한
	return (0);
}

#define MAX 1024

int cmd_cd(char **envp, char **argv)
{
	printf("cmd cd is called\n");

//	char name[MAX];//
//	char *old_pwd;
//	char *pwd;
(void)envp;

	if (argv[1][0] == '/') //절대경로
	{
		if (chdir(argv[1]) == -1)
		{
			//에러처리
		}
	}
	else if (argv[1][0] == '.') //상대경로
	{
		//chdir하고 cdrel로 절대경로로 바꿔서 pwd에 받는게 나은가?
//		chdir(cd_rel(argv));
	}
//		old_pwd = 	ft_getenv(pwd); //cd가 오류없이 작동했을 때 환경변수가 변경되어야 안전함
//	pwd = 	;//여기에 지금 경로가 들어가게 해야하는데 
	printf("After Current Directory:%s\n",getcwd(name,MAX));//
//	free(pwd);
//	free(old_pwd);
	return (0);
}

*/