#include "minishell.h"

int	check_op(char *str) // 옵션이면 0을 옵션 아니면 1을 출력한다. 
{
	if (ch_strncmp(str, "-n", 2))	//옵션 아니면 return 1
		return (1);
	str = str + 2;
	while (*str)
	{
		if (*str != 'n')
			return (1);
		str++;
	}
	return (0);
}

void	echo_print(char **envp, char *str)
{
	char	*envp;

	if (*str == '$')
	{
		str++;
		envp = ft_getenv(envp, str);	//아 이거 쓰면 안될 것 같은게 그럼 본쉘의 환경변수를 검색하게 되잖아 
		if (!envp)
			printf("");
		else
			printf("%s", envp);
	}
	else
		printf("%s", str);
}

int	cmd_echo(char **envp, char **argv)
{
	int i;
	printf("cmd echo is called\n");
(void) envp;
	i = 1;	
	while (argv[i])
		if (!check_op(argv[1]) && !check_op(argv[i]))	//	같으면(0) -> 0! // 옵션 있으므로 다음 단어부터 출력
			i++;
	while (argv[i])
	{
			echo_print(envp, argv[i]);
			if (argv[++i])		//다음 단어가 있으면 띄어쓰기 출력 하고 인덱스++
				printf(" ");
	}
	if (check_op(argv[1]))	// 값이 있으면(1이상) 옵션 없으므로 개행 넣기
		printf("\n");
	return (0);
}


//옵션 -n 
//echo는 기본적으로 개행이 붙어서 나오고 n옵션이 붙으면 개행없이 출력된다. 
/*
echo -nnnnnn도 동작한다.
echo -n-n-n은 문자열로 인식한다. 
echo -n -n -n 도 옵션으로 인식한다.
*/
