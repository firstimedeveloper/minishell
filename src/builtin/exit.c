#include "minishell.h"

//////////	ft_atoi, status 타입 longlong으로 바꾸기 

// 인자의 개수가 하나인지 확인하고 그에 맞는 exit 동작 수행
// argv가 255보다 크면 256으로 나눈 나머지로 종료된다. 
// argv가 음수면 256에서 argv 한만큼 나온다. (-2 이면 256 -2 = 254 이므로 exit 254 로 실행)
void	valid_exit_argv_num(char **argv)
{
	long long	status;

	g_e_status = 0;
	if (argv[2])
	{
		printf("minishell: exit: too many arguments\n");
		g_e_status = 1;
	}
	else
	{
		status = ft_atoll(argv[1]);
		if (g_e_status == 255)
			exit(g_e_status);
		if (status > 255)
			status = status % 256;
		else if (status < 0)
			status = status + 256;
		exit(status);
	}
}

// str이 다 숫자면 0, 아니면 1을 반환 
int	valid_exit_argv(char *str) 
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str > 47 && *str < 58) //숫자면
			str++;
		else
			return (1);
	}
	
	return (0);
}

void	cmd_exit(char **argv)
{
	printf("cmd exit is called\n");

	printf("exit\n");
	if (argv[1])
	{
		if (!valid_exit_argv(argv[1]))
			valid_exit_argv_num(argv);
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", argv[1]);
			exit(255); 
		}
	}
	else
		exit(0);
}
