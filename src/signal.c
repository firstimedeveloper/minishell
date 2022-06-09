#include "minishell.h"

void	handle_sigint( pid_t pid)
{
	char *line;
	if (pid == -1)	//자식 프로세스가 구동 중 
	{

printf("\b\b");
write(1, "\nminishell> ", 12);
		g_e_status = 1;
return ;
	}
	else
	{
		printf("\n");
		g_e_status = 130;
	}
}

void	handle_sigquit(pid_t pid)
{
	if (pid == 0)	//자식 프로세스가 구동 중 
	{

	}
	else
	{

	}
}

void	ft_signal_handler(int signo)
{
	pid_t	pid;
	int	status;

	pid = waitpid(-1, &status, WNOHANG);	//-1이 아닌 값을 반환하면 자식이 구동중인거, 아니면 -1을 반환 
//	printf("pid : %d\n", pid);
	if (signo == SIGINT)
	{
		handle_sigint(pid);
	}
	else if (signo == SIGQUIT)
	{
		handle_sigquit(pid);
	}
}