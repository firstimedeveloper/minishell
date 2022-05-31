
#include "minishell.h"

char	*get_envp_name(char *envp)
{
	char	*name;
	int	len;

	len = 0;
	while (envp[len] != '=')
		len++;
	name = (char *)malloc(sizeof(char) * (len + 1));
	name[len] = 0;
	while (--len > -1)
		name[len] = envp[len];
	return (name);
}

//e과 같은 이름의 환경변수의 값을 반환 없으면 NULL	반환
char	*ft_getenv(char **envp, char *e)
{
	char	*value;
	char	*name;
	char	**temp;

	temp = copy_envp(envp);
	while (*temp)
	{
		name = get_envp_name(*temp);
		if (ft_strncmp(name, e, ft_strlen(name), ft_strlen(e)) == 0)
			break ;
		temp++;
	}
	if (!(*temp))
		return (NULL);
	while (**temp != '=')
		(*temp)++;
	(*temp)++;
	value = ft_strdup(*temp);
	free(name);
	return (value);
}
///// 만일 환경변수는 있는데 값이 없을 떄는 어떻게 처리할 것인지 생각하기

//이미 있는 환경변수 찾아서 값만 변경하는 함수 
char	**change_envp(char **envp, char *str)
{
	char	**ch_envp;
	char	*s;			//str_name
	char	*e;			//envp_name
	int	i;

	s = get_envp_name(str);
	i = ft_envplen(envp);
	if (ft_getenv(envp, s) == NULL)	//환경변수가 존재하지 않으면
		return (envp);
	ch_envp = malloc(sizeof(char *) * (i + 1));
	ch_envp[i] = NULL;
	while (--i > -1)
	{
		e = get_envp_name(envp[i]);
		if (ft_strncmp(e, s, ft_strlen(e), ft_strlen(s)) == 0)
			ch_envp[i--] = ft_strdup(str);
		ch_envp[i] = ft_strdup(envp[i]);
		free(e);
	}
	free(s);
	return (ch_envp);
}