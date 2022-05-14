/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 16:40:58 by juhan             #+#    #+#             */
/*   Updated: 2021/05/19 18:38:27 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;
	size_t	i;

	if (!dst && !src)
		return (0);
	s = (char *)src;
	d = (char *)dst;
	i = 0;
	while (i < n)
	{
		*d = *s;
		s++;
		d++;
		i++;
	}
	return (dst);
}
