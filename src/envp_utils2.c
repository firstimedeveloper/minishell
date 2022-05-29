
#include "minishell.h"

char	*get_envp_name(char *envp)
{
	char	*name;
	int	len;

	len = 0;
	while (envp[len] != '=')
		len++;
	name = (char *)malloc(sizeof(char) * (len + 1));
	name[len] = 0;
	while (--len > -1)
		name[len] = envp[len];
	return (name);
}

char	*ft_getenv(char **envp, char *envp_name)
	//envp_name 에는 변수명만 들어오므로 
	//while문을 돌면서 환경변수를 다 가져다가 뒤에 있는 함수를 거쳐서 
	//나온값이 envp_name이랑 같은지 확인하기
	//같으면 그 값만 출력하도록 하기 
{
	char	*value =NULL;
	(void) envp;
	(void) envp_name;
//	while ()
//	{
//		ft_str
//	}
	return (value);
}

char	**change_envp(char **envp, char *str)
//이미 있는 환경변수 찾아서 값만 변경하는 함수
//이거 만들어서 export에서 가져다가 쓸까? 
{
	(void) envp;
	(void) str;

	return (NULL);
}