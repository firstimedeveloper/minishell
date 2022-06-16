/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:44:51 by juhan             #+#    #+#             */
/*   Updated: 2022/06/16 19:55:45 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_count_words_inner_loop(char const *s, size_t *count, char c)
{
	if (*s == '"')
	{
		s++;
		while (*s && *s != '"')
			s++;
		s++;
		(*count)++;
	}
	else if (*s == '\'')
	{
		s++;
		while (*s && *s != '\'')
			s++;
		s++;
		(*count)++;
	}
	else if (*s != c)
	{
		while (*s && *s != c)
			s++;
		(*count)++;
	}
	else
		s++;
	return (s);
}

size_t	ft_count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
		s = ft_count_words_inner_loop(s, &count, c);
	return (count);
}

const char	*ft_strclen_inner(char const *s, char first_char, size_t *len)
{
	if (first_char == '"' || first_char == '\'')
	{
		s++;
		(*len)++;
		while (*s)
		{
			if (*s == first_char)
				break ;
			s++;
			(*len)++;
		}
		if (*s != '\0' || *s == first_char)
		{
			s++;
			(*len)++;
		}
	}
	return (s);
}

size_t	ft_strclen(char const *s, char c)
{
	size_t	len;
	char	first_char;

	len = 0;
	first_char = *s;
	s = ft_strclen_inner(s, first_char, &len);
	while (*s)
	{
		if (*s == c)
			break ;
		s++;
		len++;
	}
	return (len);
}
