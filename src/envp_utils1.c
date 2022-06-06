
#include "minishell.h"

int	ft_envplen(char **envp)
{
	int	len;

	len = 0;
	while (*envp)
	{
		len++;
		envp++;
	}
	return (len);
}

int	check_argv(char *str)	//환경변수 
{
	int	i;

	i = 0;
	if (*str == '=' || (*str >= '0' && *str <= '9'))	//첫문자가 =나 숫자로 시작하는지 확인
	{
		printf("export: `%s': not a valid identifier\n", str);
		return (1);
	}
	while (str[i])
	{
		if ((str[i] > 47 && str[i] < 58) || (str[i] > 64 && str[i] < 91)
			|| (str[i] > 96 && str[i] < 123) || str[i] == '=')
			i++;
		else
		{
			printf("export: `%s': not a valid identifier\n", str);
			return (1);
		}
	}
	return (0);
}

char	**copy_envp(char **envp)
{
	 char	**ret;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (envp[i++])
		count++;
	ret = malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (0);
	ret[count] = 0;
	i = 0;
	while (i < count)
	{
		ret[i] = ft_strdup(envp[i]);
		i++;
	}
	return (ret);
}