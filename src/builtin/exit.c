/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:14:06 by san               #+#    #+#             */
/*   Updated: 2022/06/14 02:14:20 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	valid_exit_argv_num(char **argv)
{
	long long	status;

	g_e_status = 0;
	if (argv[2])
		ft_error(argv[0], NULL, "too many arguments", 1);
	else
	{
		status = ft_atoll(argv[1]);
		if (g_e_status == 255)
			exit(g_e_status);
		if (status > 255)
			status = status % 256;
		else if (status < 0)
			while (status > -1)
				status = status + 256;
		exit(status);
	}
}

int	valid_exit_argv(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str > 47 && *str < 58)
			str++;
		else
			return (1);
	}
	return (0);
}

void	cmd_exit(char **argv)
{
	printf("exit\n");
	if (argv[1])
	{
		if (!valid_exit_argv(argv[1]))
			valid_exit_argv_num(argv);
		else
		{
			ft_error(argv[0], argv[1], "numeric argument required", 255);
			exit(255);
		}
	}
	else
		exit(0);
}
