/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:40:53 by juhan             #+#    #+#             */
/*   Updated: 2022/03/23 12:56:50 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	count = 0;
	while (*dst && count < dstsize)
	{
		dst++;
		count++;
	}
	while (*src && count + 1 < dstsize)
	{
		*dst = *src;
		dst++;
		src++;
		count++;
	}
	if (count < dstsize)
		*dst = '\0';
	while (*src)
	{
		count++;
		src++;
	}
	return (count);
}
