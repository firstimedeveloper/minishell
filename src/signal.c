/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:57:43 by san               #+#    #+#             */
/*   Updated: 2022/06/16 15:57:46 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else
	{
		printf("\n");
		g_e_status = 130;
	}
}

void	handle_sigquit(pid_t pid)
{
	if (pid != -1)
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
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signo == SIGINT)
		handle_sigint(pid);
	else if (signo == SIGQUIT)
		handle_sigquit(pid);
}
