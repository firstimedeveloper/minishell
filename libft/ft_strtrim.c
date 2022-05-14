/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 14:49:45 by juhan             #+#    #+#             */
/*   Updated: 2021/05/19 20:40:39 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarinset(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s_len;
	char	*ret;
	size_t	from;
	size_t	to;
	size_t	i;

	if (!s1 || !set)
		return (0);
	s_len = ft_strlen(s1);
	from = 0;
	to = s_len;
	i = 0;
	while (s1[i] && ft_ischarinset(s1[i++], set))
		from++;
	i = s_len - 1;
	while (s1[i] && to > from && ft_ischarinset(s1[i--], set))
		to--;
	ret = malloc(sizeof(char) * (to - from + 1));
	if (!ret)
		return (0);
	i = 0;
	while (from < to)
		ret[i++] = s1[from++];
	ret[i] = '\0';
	return (ret);
}
