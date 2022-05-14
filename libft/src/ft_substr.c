/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:49:08 by juhan             #+#    #+#             */
/*   Updated: 2021/05/17 19:10:06 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_smaller(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

void	ft_find_len(unsigned int start, size_t slen, size_t *len)
{
	if (start > slen)
		*len = 0;
	else
		*len = ft_find_smaller((slen - start), *len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	slen;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	ft_find_len(start, slen, &len);
	ret = malloc(sizeof(char) * len + 1);
	if (!ret)
		return (0);
	i = 0;
	while (start < slen && i < len)
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
