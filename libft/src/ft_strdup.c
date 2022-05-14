/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 14:54:28 by juhan             #+#    #+#             */
/*   Updated: 2021/05/19 18:43:33 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*ret;

	len = ft_strlen(s1);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	ft_memcpy(ret, s1, len);
	ret[len] = '\0';
	return (ret);
}
