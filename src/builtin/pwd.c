/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 02:32:47 by san               #+#    #+#             */
/*   Updated: 2022/06/14 02:32:54 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		ft_error("pwd", NULL, strerror(errno), errno);
	else
	{
		printf("%s\n", path);
		g_e_status = 0;
	}
	free(path);
}
