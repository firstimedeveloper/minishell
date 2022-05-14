/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:54:44 by juhan             #+#    #+#             */
/*   Updated: 2021/05/19 18:42:18 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	if (*str == (char)c)
		return (str);
	str--;
	i--;
	while (*str && i > 0)
	{
		if (*str == (char)c)
			break ;
		str--;
		i--;
	}
	if (*str == (char)c)
		return (str);
	return (0);
}
