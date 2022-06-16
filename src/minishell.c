#include "minishell.h"

void	init_main(int argc, char **argv, t_minishell *sh, char **envp)
{
	(void)argc;
	(void)argv;
	g_e_status = 0;
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
	sh->envp = copy_envp(envp);
	sh->in = dup(0);
	sh->out = dup(1);
}

int main(int argc, char **argv, char **envp)
{
	extern int rl_catch_signals;
	rl_catch_signals = 0;
	t_minishell *sh;
	char		*line;
	pid_t		pid;
	int			status;

	sh = malloc(sizeof(t_minishell));
	init_main(argc, argv, sh, envp);
	line = NULL;
	while (1)
	{
		read_line(&line);
		if (parse(sh, line) == 1)
			continue ;
		handle_cmd(sh);
		while ((pid = waitpid(0, &status, 0)) > 0)
		{
			if (WIFEXITED(status))
				if (pid == sh->pid && sh->pid != -1)
					g_e_status = WEXITSTATUS(status);
		}
		ft_free_cmd_lst(sh);
	}
	free(sh);
	return (0);
}
