#include "minishell.h"

// 인자의 개수가 하나인지 확인하고 그에 맞는 exit 동작 수행
void	valid_exit_argv_num(t_minishell *sh, char **argv)
{
	if (argv[2])
	{
		printf("minishell: exit: too many arguments\n");
		sh->e_status = 1;
	}
	else
		exit(ft_atoi(argv[1]));
}

// str이 다 숫자면 0, 아니면 1을 반환 
int	valid_exit_argv(char *str) 
{
	while (*str)
	{
		if (*str > 47 && *str < 58) //숫자면
			str++;
		else
			return (1);
	}
	return (0);
}

void	cmd_exit(t_minishell *sh, char **argv)
{
	printf("cmd exit is called\n");

	printf("exit\n");
	if (argv[1])
	{
		if (!valid_exit_argv(argv[1]))
			valid_exit_argv_num(sh, argv);
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", argv[1]);
			exit(255); 
		}
	}
	else
		exit(0);
}
