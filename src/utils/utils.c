#include "minishell.h"

int	ch_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && *s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		i++;
		s1++;
		s2++;
	}
	if (i == n)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*av_have_eq(char *argv)
{
	while (*argv)
	{
		if (*argv == '=')
			return (argv);
		argv++;
	}
	return (NULL);
}

unsigned long long	ft_atoull(char *str)
{
	unsigned long long	val;

	val = 0;
	while (*str && (*str  >= '0' && *str <= '9'))
	{
		val *= 10;
		val += *str - '0';
		str++;
	}
	return (val);
}

int	overflow_exit(char *str, int neg)
{
	unsigned long long	value;

	value = ft_atoull(str);
	if (neg < 0)
	{
		if (value > 9223372036854775808U)
		{
			g_e_status = 255;
			return (1);
		}
	}
	else
	{
		if (value > 9223372036854775807U)
		{
			g_e_status = 255;
			return (1);
		}
	}
	return (0);
}

long long	ft_atoll(const char *str)
{
	long long	val;
	int			neg;

	val = 0;
	neg = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	if (overflow_exit((char *)str, neg) == 1)
	{
		printf("bash: exit: %s: numeric argument required\n", str);
		return (0);
	}
	while (*str && (*str  >= '0' && *str <= '9'))
	{
		val = val * 10 + *str - '0';
		str++;
	}
	val *= neg;
	return (val);
}
