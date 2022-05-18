#include "minishell.h"

int	is_builtin(t_cmd *cmd, char *content)
{
	(void)cmd;
	int	i;
	const char	*builtin[7] = {
		"cd",
		"echo",
		"env",
		"exit",
		"export",
		"pwd",
		"unset"
	};
	const size_t	builtin_len[7] = {
		2,
		4,
		3,
		4,
		6,
		3,
		5
	};

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(builtin[i], content, ft_strlen(content), builtin_len[i]))
			return (i+1);
		i++;
	}
	return 0;

}

int	excecute_builtin(t_cmd *cmd, int builtin)
{
	(void)cmd;
	if (builtin == TYPE_CMD_CD)
		return (cmd_cd(cmd));
	else if (builtin == TYPE_CMD_ECHO)
		return (cmd_echo(cmd));
	else if (builtin == TYPE_CMD_ENV)
		return (cmd_env(cmd));
	else if (builtin == TYPE_CMD_EXIT)
		return (cmd_exit(cmd));
	else if (builtin == TYPE_CMD_EXPORT)
		return (cmd_export(cmd));
	else if (builtin == TYPE_CMD_PWD)
		return (cmd_pwd(cmd));
	else if (builtin == TYPE_CMD_UNSET)
		return (cmd_unset(cmd));

	return (0);
}

int	excecute_find(t_cmd *cmd)
{
	(void)cmd;
	return (1);
}

t_cmd	*excecute_cmd(t_minishell *sh, t_cmd *cmd)
{
	t_cmd	*next;
	(void)sh;
	// check if built in,
	int	tmp;

	tmp = is_builtin(cmd, cmd->content);
	next = cmd;
	while (next)
	{
		if (next->type == TYPE_PIPE)
		{
			next = next->next;
			break ;
		}

		next = next->next;
	}
	if (tmp)
		excecute_builtin(cmd, tmp);
	else
		excecute_find(cmd);

	return (next);
}

int	handle_cmd(t_minishell *sh)
{
	t_cmd	*cur;

	cur = sh->cmd_list;
	while (cur)
	{
		if (cur->type == TYPE_CMD)
		{
			cur = excecute_cmd(sh, cur);
		}
	}
	return (1);
}
