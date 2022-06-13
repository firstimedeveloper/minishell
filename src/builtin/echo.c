/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:09:48 by san               #+#    #+#             */
/*   Updated: 2022/06/14 02:12:57 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_op(char *str)
{
	if (ch_strncmp(str, "-n", 2))
		return (1);
	str = str + 2;
	while (*str)
	{
		if (*str != 'n')
			return (1);
		str++;
	}
	return (0);
}

void	cmd_echo(t_minishell *sh, char **argv)
{
	int	i;

	(void)sh;
	i = 1;
	while (argv[i] && !check_op(argv[i]))
		i++;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[++i])
			printf(" ");
	}
	if ((argv[1] && check_op(argv[1])) || argv[1] == NULL)
		printf("\n");
	g_e_status = 0;
}
