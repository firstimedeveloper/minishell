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

//환경변수이름이 조건에 맞게 입력되었는지 확인한다. 
//조건 : 첫문자가 =나 숫자로 시작하지 않는다. 
//    : 환경변수이름이 숫자, 대문자, 소문자로만 이루어진다.
// input : str -> NAME=VALUE 꼴
// output : 맞으면 0, invalid면 1을 반환한다. 
int	check_argv_name(char *str, char *cmd)
{
	int	i;

	i = 0;
	if (*str == '=' || (*str >= '0' && *str <= '9'))	//첫문자가 =나 숫자로 시작하는지 확인
	{
		printf("minishell: %s: `%s': not a valid identifier\n", cmd, str);
		g_e_status = 1;
		return (1);
	}
	while (str[i] && str[i] != '=')
	{
		if ((str[i] > 47 && str[i] < 58) || (str[i] > 64 && str[i] < 91)	//환경변수이름이 숫자, 대문자, 소문자로만 이루어졌는지 확인한다. 
			|| (str[i] > 96 && str[i] < 123))
			i++;
		else
		{
			printf("minishell: %s: `%s': not a valid identifier\n", cmd, str);
			g_e_status = 1;
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