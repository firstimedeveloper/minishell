#include "minishell.h"

void	init_term(struct termios *term)
{
	tcgetattr(STDIN, term);
	term->c_lflag &= ~ICANON;
	term->c_lflag &= ~ECHO;
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	tcsetattr(STDIN, TCSANOW, term);
}

void handler(int signum)
{
    if (signum == SIGINT)
	{
		printf("\n");
	}
	else if (signum == SIGTERM)
	{
		printf(" exit\n");
		exit(-1);
	}
	else
		return ;
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	extern int rl_catch_signals;
	rl_catch_signals = 0;
	signal(SIGINT, handler);
	signal(SIGTERM, handler);
	signal(SIGQUIT, handler);
	t_minishell sh;
	//struct termios term;
	char		*line;

	//init_term(&term);
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
