/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 16:26:02 by san               #+#    #+#             */
/*   Updated: 2022/06/16 16:26:05 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	get_exit_status(t_minishell *sh)
{
	pid_t		pid;
	int			status;

	while (1)
	{
		pid = waitpid(0, &status, 0);
		if (pid <= 0)
			break ;
		if (WIFEXITED(status))
			if (pid == sh->pid && sh->pid != -1)
				g_e_status = WEXITSTATUS(status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	extern int	rl_catch_signals;
	t_minishell	*sh;
	char		*line;

	rl_catch_signals = 0;
	sh = malloc(sizeof(t_minishell));
	init_main(argc, argv, sh, envp);
	line = NULL;
	while (1)
	{
		read_line(&line);
		if (parse(sh, line) == 1)
			continue ;
		handle_cmd(sh);
		get_exit_status(sh);
		ft_free_cmd_lst(sh);
	}
	free(sh);
	return (0);
}
