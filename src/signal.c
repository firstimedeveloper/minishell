#include "minishell.h"

void	handle_sigint(pid_t pid)
{
	if (pid == -1)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_e_status = 1;
	}
	else					//자식 프로세스가 구동 중
	{
		printf("\n");
		g_e_status = 130;
	}
}

void	handle_sigquit(pid_t pid)
{
	if (pid != -1)			//자식 프로세스가 구동 중
	{
		printf("Quit: 3\n");
		rl_replace_line("", 1);
		g_e_status = 131;
	}
	else
		g_e_status = 0;
}

void	ft_signal_handler(int signo)
{
	pid_t	pid;
	int	status;

	pid = waitpid(-1, &status, WNOHANG);	//-1이 아닌 값을 반환하면 자식이 구동중인거, 아니면 -1을 반환
//	printf("pid : %d\n", pid);
	if (signo == SIGINT)
		handle_sigint(pid);
	else if (signo == SIGQUIT)
		handle_sigquit(pid);
}
