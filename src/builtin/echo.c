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
	char	*envp_value;

	if (*str == '$')
	{
		str++;
		if (*str != '?')
		{
			envp_value = ft_getenv(envp, str);
			if (!envp_value)
				printf("");
			else
			{
				printf("%s", envp_value);
				free(envp_value);
			}
		}
		else
			printf("%d", g_e_status);
	}
	else
		printf("%s", str);
}

void	cmd_echo(t_minishell *sh, char **argv)
{
	int i;

	i = 1;	
	while (!check_op(argv[i]))	//	같으면(0) -> 0! // 옵션 있으므로 다음 단어부터 출력
		i++;
	while (argv[i])
	{
		echo_print(sh->envp, argv[i]);
		if (argv[++i])		//다음 단어가 있으면 띄어쓰기 출력 하고 인덱스++
			printf(" ");
	}
	if (check_op(argv[1]))	// 값이 있으면(1이상) 옵션 없으므로 개행 넣기
		printf("\n");
	g_e_status = 0;
}


//옵션 -n 
//echo는 기본적으로 개행이 붙어서 나오고 n옵션이 붙으면 개행없이 출력된다. 
/*
echo -nnnnnn도 동작한다.
echo -n-n-n은 문자열로 인식한다. 
echo -n -n -n 도 옵션으로 인식한다.
*/

//////확인해봐야하는 부분 : echo -n -n -c -n dfs 에서 마지막 -n 나오는지 
