/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 16:32:37 by juhan             #+#    #+#             */
/*   Updated: 2021/05/19 18:39:15 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cur;
	size_t			i;

	cur = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)c == *cur)
			return (cur);
		cur++;
		i++;
	}
	return (0);
}
