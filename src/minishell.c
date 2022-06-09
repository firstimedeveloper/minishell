#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_minishell sh;
	(void)sh;
	char		*line;

	sh.envp = copy_envp(envp);
	g_e_status = 0;
	//sh.envp = envp;	minishell만의 환경변수리스트를 만들어야한다고 생각해서 위의 코드 살림
	line = NULL;
	signal(SIGINT, (void *)ft_signal_handler);	// ctrl c
	signal(SIGQUIT, (void *)ft_signal_handler);	// ctrl "\"
	while (1)
	{
		read_line(&line);
		if (parse(&sh, line) == 1)
			continue ;
		handle_cmd(&sh);
	}

	return (0);
}
