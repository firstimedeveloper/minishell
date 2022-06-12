
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

void	change_envp(char ***envp, char *str)
{
	char	**ch_envp;
	char	*s;
	char	*e;
	int	i;

	s = get_envp_name(str);
	i = ft_envplen(*envp);
	if (ft_getenv(*envp, s) == NULL)
		return ;
	ch_envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!ch_envp)
		exit (1);	
	ch_envp[i] = NULL;
	while (--i > -1)
	{
		e = get_envp_name((*envp)[i]);
		if (ft_strncmp(e, s, ft_strlen(e), ft_strlen(s)) == 0)
			ch_envp[i--] = ft_strdup(str);
		ch_envp[i] = ft_strdup((*envp)[i]);
		free(e);
	}
	free(s);
	*envp = ch_envp;
}

int	ch_envp_with_name(char ***envp, char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	change_envp(envp, str);

// int	i;
// i = 0;
// 	while (i < ft_envplen(*envp))
// 	{
// 		printf("cd : %s\n", (*envp)[i]);
// 		i++;
// 	}

	free(str);
	return (0);
}