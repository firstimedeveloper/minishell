#include "minishell.h"

void	set_signal(struct termios *term)
{
	tcgetattr(STDIN, term);
	term->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN, TCSANOW, term);
	signal(SIGINT, ft_signal_handler);	// ctrl c
	signal(SIGQUIT, ft_signal_handler);	// ctrl "\"
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	extern int rl_catch_signals;
	rl_catch_signals = 0;
//	signal(SIGTERM, handler);
	t_minishell sh;
//	struct termios term;
	char		*line;

//	set_signal(&term);
	sh.envp = copy_envp(envp);
	g_e_status = 0;
	signal(SIGINT, ft_signal_handler);	// ctrl c
	signal(SIGQUIT, ft_signal_handler);	// ctrl "\"
	//sh.envp = envp;	minishell만의 환경변수리스트를 만들어야한다고 생각해서 위의 코드 살림
	line = NULL;
	while (1)
	{
		read_line(&line);
		if (parse(&sh, line) == 1)
			continue ;
		handle_cmd(&sh);
	}

	return (0);
}
