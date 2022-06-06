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