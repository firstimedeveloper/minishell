/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:34:48 by juhan             #+#    #+#             */
/*   Updated: 2021/05/19 18:45:02 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h_cur;
	char	*n_cur;
	size_t	i;
	size_t	n_len;

	i = 0;
	n_len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && i + n_len <= len)
	{
		h_cur = (char *)haystack;
		n_cur = (char *)needle;
		while (*n_cur && *h_cur == *n_cur)
		{
			h_cur++;
			n_cur++;
		}
		if (*n_cur == '\0')
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (0);
}
