#include "minishell.h"

// char	*loop_env(char *str, int *i, char *ret)
// {
// 	int		len;

// 	(void)str;
// 	(void)i;
// 	(void)len;
// 	len = 0;
// 	return (ret);
// }

// char	*loop(char *str, int *i, char *ret, char c)
// {
// 	char	*ret_cpy;
// 	char	*temp;
// 	int		len;

// 	len = 0;
// 	ret_cpy = ret;
// 	while (str[*i] && str[*i] != c)
// 	{
// 		len++;
// 		(*i)++;
// 	}
// 	if (len > 0)
// 	{
// 		temp = ft_strldup(&str[*i - len], len);
// 		ret = ft_strjoin(ret_cpy, temp);
//  		fprintf(stderr, "ret=%s, %s, %d, %s, %d\n", ret, &str[*i], *i, temp, len);
// 		free(ret_cpy);
// 		free(temp);
// 	}
// 	if (str[*i] == c)
// 		(*i)++;
// 	return (ret);
// }

// char	*loop2(char *str, int *i, char *ret, char c)
// {
// 	char	*ret_cpy;
// 	char	*temp;
// 	int		len;

// 	len = 0;
// 	ret_cpy = ret;
// 	while (str[*i] && str[*i] != c)
// 	{
// 		len++;
// 		(*i)++;
// 	}
// 	if (len > 0)
// 	{
// 		temp = ft_strldup(&str[*i - len], len);
// 		ret = ft_strjoin(ret_cpy, temp);
//  		fprintf(stderr, "ret=%s, %s, %d, %s, %d\n", ret, &str[*i], *i, temp, len);
// 		free(ret_cpy);
// 		free(temp);
// 	}
// 	if (str[*i] == c)
// 		(*i)++;
// 	return (ret);
// }

// char	*loop3(char *str, int *i, char *ret, int c1, char c2)
// {
// 	char	*ret_cpy;
// 	char	*temp;
// 	char	*env;
// 	int		len;
// 	int		len;

// 	len = 0;
// 	ret_cpy = ret;
// 	while (str[*i] && str[*i] != c1 && str[*i] != c2)
// 	{
// 		ret_cpy = ret;
// 		if (str[*i] == '$')
// 		{
// 			len = 0;
// 			while (str[*i] && str[(*i)++] != '"')
// 				len++;
// 			temp = ft_strldup(&str[*i-len]+1, len-1);
// 			env = getenv(temp);
// 			if (!env)
// 				continue ;
// 			fprintf(stderr, "ret=%s, %s, %s, %s, %d, %d\n", ret, &str[*i], temp, env, len, *i);
// 			ret = ft_strjoin(ret_cpy, env);
// 			free(temp);
// 			free(ret_cpy);
// 	}
// 		len++;
// 		(*i)++;
// 	}
// 	if (len > 0)
// 	{
// 		temp = ft_strldup(&str[*i - len], len);
// 		ret = ft_strjoin(ret_cpy, temp);
//  		fprintf(stderr, "ret=%s, %s, %d, %s, %d\n", ret, &str[*i], *i, temp, len);
// 		free(ret_cpy);
// 		free(temp);
// 	}
// 	// if (str[*i] == c1 || str[*i] == c2)
// 	// 	(*i)++;
// 	return (ret);
// }

// char	*handle_expansion(t_minishell *sh, char *str)
// {
// 	(void)sh;
// 	char	*ret;
// 	int		i;

// 	i = 0;
// 	ret = malloc(sizeof(char));
// 	ret[0] = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '"')
// 		{
// 			ret = loop(str, &i, ret, '"');
// 		} else if (str[i] == '\'')
// 		{
// 			ret = loop2(str, &i, ret, '\'');
// 		} else
// 		{
// 			ret = loop3(str, &i, ret, '\'', '"');
// 		}
// 		i++;
// 	}
// 	return (ret);
// }
// char	*new_str(char *str, int i, int len, char *ret_cpy)
// {
// 	char	*ret;
// 	char	*temp;

// 	ret = ret_cpy;
// 	temp = ft_strldup(&str[i - len], len);
// 	ret = ft_strjoin(ret_cpy, temp);
//  	fprintf(stderr, "\tret=%s, %s, %d, %s, %d\n", ret, &str[i], i, temp, len);
// 	free(ret_cpy);
// 	free(temp);
// 	return (ret);
// }
// char	*handle_expansion(t_minishell *sh, char *str) {
// 	(void)sh;
// 	char	*ret;
// 	char	*ret_cpy;
// 	char	*temp;
// 	char	*env;
// 	int		i;
// 	int		len;
// 	int		len;

// 	i = -1;
// 	ret = malloc(sizeof(char));
// 	ret[0] = 0;
// 	while (str[++i])
// 	{
// 		ret_cpy = ret;
// 		if (str[i] == '"')
// 		{
// 			len = 0;
// 			while (str[i] && str[i] != '"')
// 			{
// 				if (str[i] == '$')
// 				{
// 					len = 0;
// 					while (str[i] && str[i++] != '"')
// 						len++;
// 					temp = ft_strldup(&str[i], len);
// 					env = getenv(temp);
// 					ret = ft_strjoin(ret_cpy, env);
// 					fprintf(stderr, "ret=%s, %s, %s, %s, %d, %d\n", ret, &str[i], temp, env, len, i);
// 					free(temp);
// 					free(ret_cpy);
// 				}
// 				len++;
// 				i++;
// 			}
// 			ret_cpy = ret;
// 			temp = ft_strldup(&str[i - len], len);
// 			ret = ft_strjoin(ret_cpy, temp);
// 			free(ret_cpy);
// 			free(temp);
// 		}
// 		else if (str[i] == '\'')
// 		{
// 			len = 0;
// 			while (str[i] && str[i] != '\'')
// 			{
// 				len++;
// 				i++;
// 			}
// 			ret = new_str(str, i, len, ret);
// 		}
// 		else
// 		{
// 			ret_cpy = ret;
// 			while (str[i] && str[i] != '"' && str[i] != '\'')
// 			{
// 				if (str[i] == '$')
// 				{
// 					len = 0;
// 					while (str[i] && str[i++] != '"')
// 						len++;
// 					temp = ft_strldup(&str[i-len]+1, len-1);
// 					env = ft_getenv(sh->envp, temp);
// 					if (env)
// 					{
// 						ret = ft_strjoin(ret_cpy, env);
// 						fprintf(stderr, "ret=%s, %s, %s, %s, %d, %d\n", ret, &str[i], temp, env, len, i);
// 						free(temp);
// 						free(ret_cpy);
// 					}
// 				}
// 				else
// 				{
// 					len = 0;
// 					while (str[i] && str[i] != '"' && str[i] != '$')
// 					{
// 						i++;
// 						len++;
// 					}
// 					if (len > 0)
// 					{
// 						ret = new_str(str, i, len, ret);
// 					}
// 				}
// 				i++;
// 			}
// 		}
// 	}
// 	return (ret);
// }

char	*new_str(char *str, int i, int len, char *ret_cpy)
{
	char	*ret;
	char	*temp;

	ret = ret_cpy;
	temp = ft_strldup(&str[i - len], len);
	ret = ft_strjoin(ret_cpy, temp);
 	fprintf(stderr, "\tret=%s, %s, %d, %s, %d\n", ret, &str[i], i, temp, len);
	free(ret_cpy);
	free(temp);
	return (ret);
}

char	*handle_expansion(t_minishell *sh, char *str) {
	(void)sh;
	char	ret[100];
	char	*temp;
	char	*env;
	int		i;
	int		len;
	int		double_flag;
	int		single_flag;

	single_flag = 0;
	double_flag = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (single_flag)
			{
				ft_strlcat(ret, "\"", 100);
				i++;
			}
			else
			{
				if (double_flag)
					double_flag--;
				else
					double_flag++;
				i++;
			}
		}
		else if (str[i] == '\'')
		{
			if (double_flag)
			{
				ft_strlcat(ret, "'", 100);
				i++;
			}
			else
			{
				if (single_flag)
					single_flag--;
				else
					single_flag++;
				i++;
			}
		}
		else if (str[i] == '$')
		{
			if (double_flag || (!double_flag && !single_flag))
			{
				if (str[i + 1] == '?')
				{
					ft_strlcat(ret, ft_itoa(g_e_status), 100);
					i += 2;
				}
				else
				{
					len = 0;
					while (str[i + len] && str[i + len] != '"' && str[i + len] != '\'')
						len++;
					if (len > 0)
					{
						temp = ft_strldup(&str[i + 1], len-1);
						env = getenv(temp);
						fprintf(stderr, "ret=%s, %s, %s, %s, %d, %d\n", ret, &str[i + 1], temp, env, len, i);
						if (env)
						{
							// ret = ft_strjoin(ret_cpy, env);
							ft_strlcat(ret, env, 100);
							free(temp);
							// free(ret_cpy);
							i += len;
						}
						else
							i++;
					}
					else
					{
						ft_strlcat(ret, "$", 100);
						i += 2;
					}
				}
			}
			else
			{
				ft_strlcat(ret, "$", 100);
				i++;
			}
		}
		else
		{
			len = 0;
			// while (str[i] &&
			// 	((str[i] != '\'' && ((!single_flag && !double_flag) || double_flag)) ||
			// 	(str[i] != '"' && ((!single_flag && !double_flag) || single_flag))))
			while (str[i + len] && str[i + len] != '\'' && str[i + len] != '"' && str[i + len] != '$')
			{
				len++;
			}
			if (len > 0)
			{
				temp = ft_strldup(&str[i], len);
				ft_strlcat(ret, temp, 100);
				// ret = ft_strjoin(ret_cpy, temp);
				// fprintf(stderr, "ret=%s, %s, %s, %s, %d, %d\n", ret, &str[i-len], temp, env, len, i);
				// free(ret_cpy);
				free(temp);
				i += len;
			}
		}
	}
	return (ft_strdup(ret));
}
