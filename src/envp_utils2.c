#include "minishell.h"

char	*get_envp_name(char *envp)
{
	char	*name;
	int	len;

	len = 0;
	while (envp[len] && envp[len] != '=')
		len++;
	name = (char *)malloc(sizeof(char) * (len + 1));
	if (!name)
		exit(errno);
	name[len] = '\0';
	while (--len > -1)
		name[len] = envp[len];
	return (name);
}

char	*get_env_value(char *env)
{
	char	*value;
	int		i;

	i = 0;
	while (env[i] != '=')
		i++;
	i++;
	value = ft_strdup(&env[i]);
	return (value);
}

char	*ft_getenv(char **envp, char *e)
{
	char	*name;

	while (*envp)
	{
		name = get_envp_name(*envp);
		if (ft_strncmp(name, e, ft_strlen(name), ft_strlen(e)) == 0)
			break ;
		ft_free(name);
		envp++;
	}
	if (!(*envp))
		return (NULL);
	ft_free(name);
	return (get_env_value(*envp));
}		// 이 함수를 쓸 때 리턴받은 값을 프리해줘야한다. 

void	change_envp(char ***envp, char *str, char *env_name) 
{
	char	**ch_envp;
	char	*e;
	int	i;

	if (str == NULL)
		return ;
	i = ft_envplen(*envp);	
	ch_envp = malloc(sizeof(char *) * (i + 1));
	if (!ch_envp)
		ft_exit(errno);	
	ch_envp[i] = NULL;
	while (--i > -1)
	{
		e = get_envp_name((*envp)[i]);
		if (ft_strncmp(e, env_name, ft_strlen(e), ft_strlen(env_name)) == 0)
			ch_envp[i--] = ft_strjoin(env_name, str);
		ch_envp[i] = ft_strdup((*envp)[i]);
		ft_free(e);
	}
	ft_free_all(*envp);
	*envp = ch_envp;
}

int	ch_envp_with_name(char ***envp, char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin("=", s2);
	change_envp(envp, str, s1);
	ft_free(str);
	return (0);
}