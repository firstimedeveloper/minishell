/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:15:36 by juhan             #+#    #+#             */
/*   Updated: 2022/06/15 18:15:41 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(char *command, char *argv, char *err_msg, int err_code)
{
	if (argv)
		printf("minishell: %s: %s: %s\n", command, argv, err_msg);
	else
		printf("minishell: %s: %s\n", command, err_msg);
	g_e_status = err_code;
}

void	ft_error_2(char *command, char *argv, int err_code)
{
	printf("minishell: %s: `%s': not a valid identifier\n", command, argv);
	g_e_status = err_code;
}

void	ft_error_redir(char *err_msg, int err_code, int fd)
{
	printf("minishell: %s\n", err_msg);
	ft_close(fd);
	fd = -1;
	g_e_status = err_code;
}

void	ft_error_open(char *err_msg, int err_code)
{
	printf("minishell: %s\n", err_msg);
	g_e_status = err_code;
}
