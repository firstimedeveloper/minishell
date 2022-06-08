
#include "minishell.h"

// 들어온 envp의 문자열에서 환경변수이름만 걸러준다. 
// input : envp -> NAME=VALUE 꼴
// output : 문자열에서 환경변수이름만 반환 
char	*get_envp_name(char *envp)
{
	char	*name;
	int	len;

	len = 0;
	while (envp[len] && envp[len] != '=')
		len++;
	name = (char *)malloc(sizeof(char) * (len + 1));
	if (!name)
		exit(1);	////////////말록 에러 좀 더 고민해보기 
	name[len] = '\0';
	while (--len > -1)
		name[len] = envp[len];
	return (name);
}

// e과 같은 이름의 환경변수의 값을 반환
// input : envp -> 환경변수 목록 / e -> 찾고자하는 환경변수이름
// output : e과 같은 이름의 환경변수의 값을 반환 / 없으면 NULL을 반환
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
//	printf("getemv when value is null : %s\n", value); //환경변수는 있는데 값이 없을 떄 아무것도 출력되지 않는다. 하지만 change_envp는 작동시킨다.
	free(name);
	return (value);
}

//이미 있는 환경변수 찾아서 값만 변경하는 함수 str -> NAME=VALUE 형태
int	change_envp(char ***envp, char *str)
{
	char	**ch_envp;
	char	*s;			//str_name
	char	*e;			//envp_name
	int	i;

	s = get_envp_name(str);
	i = ft_envplen(*envp);
	if (ft_getenv(*envp, s) == NULL)	//환경변수가 존재하지 않으면
		return (-1);
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
	return (0);
}

int	ch_envp_with_name(char ***envp, char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	change_envp(envp, str);
	free(str);
	return (0);
}