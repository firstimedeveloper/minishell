/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:48:43 by juhan             #+#    #+#             */
/*   Updated: 2021/05/17 19:10:48 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (0);
	i = 0;
	while (*s1)
	{
		ret[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		ret[i] = *s2;
		s2++;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
