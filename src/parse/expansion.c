#include "minishell.h"

char	*handle_expansion(t_minishell *sh, char *str)
{
	char	ret[MAX];
	char	*temp;
	char	*env;
	int		i;
	int		len;
	int		double_flag;
	int		single_flag;

	single_flag = 0;
	double_flag = 0;
	ft_bzero(ret, MAX);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (single_flag)
			{
				ft_strlcat(ret, "\"", MAX);
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
				ft_strlcat(ret, "'", MAX);
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
					temp = ft_itoa(g_e_status);
					ft_strlcat(ret, temp, MAX);
					free(temp);
					i += 2;
				}
				else
				{
					len = 0;
					while (str[i + len] && str[i + len] != ' ' && str[i + len] != '"' && str[i + len] != '\'')
						len++;
					if (len > 1)
					{
						temp = ft_strldup(&str[i + 1], len-1);
						env = ft_getenv(sh->envp, temp);
						fprintf(stderr, "program:\tret=%s, %s, %s, %s, %d, %d\n", ret, &str[i + 1], temp, env, len, i);
						if (env)
						{
							ft_strlcat(ret, env, MAX);
							ft_free(temp);
							ft_free(env);
						}
						i += len;
					}
					else
					{
						ft_strlcat(ret, "$", MAX);
						i += 2;
					}
				}
			}
			else
			{
				ft_strlcat(ret, "$", MAX);
				i++;
			}
		}
		else
		{
			len = 0;
			while (str[i + len] && str[i + len] != '\'' && str[i + len] != '"' && str[i + len] != '$')
			{
				len++;
			}
			if (len > 0)
			{
				temp = ft_strldup(&str[i], len);
				ft_strlcat(ret, temp, MAX);
				free(temp);
				i += len;
			}
		}
	}
	return (ft_strdup(ret));
}
