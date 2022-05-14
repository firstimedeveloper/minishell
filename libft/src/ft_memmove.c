/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:07:17 by juhan             #+#    #+#             */
/*   Updated: 2021/05/19 18:39:35 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;
	size_t	i;

	d = (char *)dst;
	s = (char *)src;
	if (d == s || len == 0)
		return (dst);
	else if (d > s && d - s < (long)len)
	{
		i = len + 1;
		while (--i > 0)
			d[i - 1] = s[i - 1];
		return (dst);
	}
	else if (s > d && s - d < (long)len)
	{
		i = -1;
		while (++i < len)
			d[i] = s[i];
		return (dst);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}
