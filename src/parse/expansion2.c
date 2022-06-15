/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:49:08 by juhan             #+#    #+#             */
/*   Updated: 2022/06/15 16:27:39 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_and_increment(char *ret, char *str, int *i, int inc)
{
	ft_strlcat(ret, str, MAX);
	*i += inc;
}

void	set_flag_and_increment(int *flag, int *i)
{
	if (*flag)
		*flag -= 1;
	else
		*flag += 1;
	*i += 1;
}
