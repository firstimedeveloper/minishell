/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 14:49:08 by juhan             #+#    #+#             */
/*   Updated: 2022/06/15 16:27:39 by juhan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case_non_special_char(char *ret, char *str, int *i)
{
	char	*temp;
	int		len;

	len = 0;
	while (str[*i + len] && str[*i + len] != '\''
		&& str[*i + len] != '"' && str[*i + len] != '$')
		len++;
	if (len > 0)
	{
		temp = ft_strldup(&str[*i], len);
		ft_strlcat(ret, temp, MAX);
		ft_free(temp);
		*i += len;
	}
}

void	inner_elseif_double_quote(t_minishell *sh, char *ret, char *str, int *i)
{
	char	*temp;
	char	*env;
	int		len;

	len = 0;
	while (str[*i + len] && str[*i + len] != ' '
		&& str[*i + len] != '"' && str[*i + len] != '\'')
		len++;
	if (len > 1)
	{
		temp = ft_strldup(&str[*i + 1], len - 1);
		env = ft_getenv(sh->envp, temp);
		if (env)
		{
			ft_strlcat(ret, env, MAX);
			ft_free(env);
		}
		ft_free(temp);
		*i += len;
	}
	else
		append_and_increment(ret, "$", i, 2);
}

void	case_dollar_sign(t_minishell *sh, char *ret, char *str, int *i)
{
	char	*temp;

	if (str[*i + 1] == '?')
	{
		temp = ft_itoa(g_e_status);
		ft_strlcat(ret, temp, MAX);
		free(temp);
		*i += 2;
	}
	else
		inner_elseif_double_quote(sh, ret, str, i);
}

static void	init_expansion(char *ret, int *f1, int *f2, int *i)
{
	*f1 = 0;
	*f2 = 0;
	ft_bzero(ret, MAX);
	*i = 0;
}

char	*handle_expansion(t_minishell *sh, char *str)
{
	char	ret[MAX];
	int		i;
	int		double_flag;
	int		single_flag;

	init_expansion(ret, &single_flag, &double_flag, &i);
	while (str[i])
		if (str[i] == '"')
			if (single_flag)
				append_and_increment(ret, "\"", &i, 1);
	else
		set_flag_and_increment(&double_flag, &i);
	else if (str[i] == '\'')
		if (double_flag)
			append_and_increment(ret, "'", &i, 1);
	else
		set_flag_and_increment(&single_flag, &i);
	else if (str[i] == '$')
		if (double_flag || (!double_flag && !single_flag))
			case_dollar_sign(sh, ret, str, &i);
	else
		append_and_increment(ret, "$", &i, 1);
	else
		case_non_special_char(ret, str, &i);
	return (ft_strdup(ret));
}
