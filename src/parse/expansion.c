#include "minishell.h"

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
						// fprintf(stderr, "ret=%s, %s, %s, %s, %d, %d\n", ret, &str[i + 1], temp, env, len, i);
						if (env)
						{
							ft_strlcat(ret, env, 100);
							free(temp);
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
			while (str[i + len] && str[i + len] != '\'' && str[i + len] != '"' && str[i + len] != '$')
			{
				len++;
			}
			if (len > 0)
			{
				temp = ft_strldup(&str[i], len);
				ft_strlcat(ret, temp, 100);
				free(temp);
				i += len;
			}
		}
	}
	return (ft_strdup(ret));
}
