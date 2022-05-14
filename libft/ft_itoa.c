/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 17:41:06 by juhan             #+#    #+#             */
/*   Updated: 2021/05/19 18:48:38 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_length(long n)
{
	int	i;

	i = 0;
	if (n <= 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ret;
	long	num;
	int		i;

	len = get_length(n);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (0);
	num = n;
	i = 0;
	if (num == 0)
		ret[0] = '0';
	else if (num < 0)
	{
		ret[i] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		ret[len - i++ - 1] = '0' + num % 10;
		num /= 10;
	}
	ret[len] = '\0';
	return (ret);
}
