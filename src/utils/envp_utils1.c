/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:15:36 by juhan             #+#    #+#             */
/*   Updated: 2022/06/15 18:15:41 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_envplen(char **envp)
{
	int	len;

	len = 0;
	while (*envp)
	{
		len++;
		envp++;
	}
	return (len);
}

int	check_argv_name(char *str, char *cmd)
{
	int	i;

	i = 0;
	if (*str == '=' || (*str >= '0' && *str <= '9'))
	{
		ft_error_2(cmd, str, 1);
		return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if ((str[i] > 47 && str[i] < 58) || (str[i] > 64 && str[i] < 91)
			|| (str[i] > 96 && str[i] < 123) || str[i] == '_')
			i++;
		else
		{
			ft_error_2(cmd, str, 1);
			return (1);
		}
	}
	return (0);
}

char	**copy_envp(char **envp)
{
	char	**ret;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (envp[i++])
		count++;
	ret = malloc(sizeof(char *) * (count + 1));
	if (!ret)
		exit(errno);
	ret[count] = 0;
	i = 0;
	while (i < count)
	{
		ret[i] = ft_strdup(envp[i]);
		i++;
	}
	return (ret);
}
