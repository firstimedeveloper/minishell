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

void	ft_free_double(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

// export에서 argv가 값을 변경할 수 있는 조건을 갖췄는지 판별 (= 이하의 값을 가지고 있다.)
// input : argv -> 판별하고자 하는 argv문자열
// output : envp change가 가능하면 1, 불가능하면 0을 반환
int	av_have_eq(char *argv)
{
	while (*argv)
	{
		if (*argv == '=')
			return (1);
		argv++;
	}
	return (0);
}

// void	overflow_exit(char *str, int neg)
// {
// 	char	*longlong;
// 	int		i;

// 	longlong = "9223372036854775807";
// 	i = -1;

// 	if (ft_strlen(str) > 20)
// 	{
// 		//
// 	}

// 	if ((*str == '+' && ft_strlen(str) < 21dfkgjds;lk) || (*str  >= '0' && *str <= '9'))
// 	{
// 		while (++i < 20)	//양수로 longlong보다 더 큰지 확인
// 		{
// 			if (str[i] > longlong[i] && ft_strlen(str) == 20)
// 			{
// 				//숫자 넘어가는 exit error
// 			}
// 		}
// 	}
// 	else if (*str == '-')
// 	{
// 		++i;
// //		while (++i < 20)
// 	}
// }

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
	//여기에 longlong넘는지 확인 neg같이 받는다.
	while (*str && (*str  >= '0' && *str <= '9'))
	{
		val *= 10;
		val += *str - '0';
		str++;
	}
	val *= neg;
	if (*str)
	{
		//숫자가 아니다.
	}
	return (val);
}

void	ft_error(t_minishell *sh, char *command, char *err_msg, int err_code)
{
	(void)sh;
	printf("minishell: %s: %s\n", command, err_msg);
	// if (err_code != 0)
		//g_e_status = err_code;
	exit(err_code);
}
