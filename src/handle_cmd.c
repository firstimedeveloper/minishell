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

int	excecute_builtin(char **argv, int builtin)
{
	if (builtin == TYPE_CMD_CD)
		return (cmd_cd(argv));
	else if (builtin == TYPE_CMD_ECHO)
		return (cmd_echo(argv));
	else if (builtin == TYPE_CMD_ENV)
		return (cmd_env(argv));
	else if (builtin == TYPE_CMD_EXIT)
		return (cmd_exit(argv));
	else if (builtin == TYPE_CMD_EXPORT)
		return (cmd_export(argv));
	else if (builtin == TYPE_CMD_PWD)
		return (cmd_pwd(argv));
	else if (builtin == TYPE_CMD_UNSET)
		return (cmd_unset(argv));

	return (0);
}

int	excecute_find(t_minishell *sh, char **argv)
{
	(void)sh;
	char	**paths;
	char	*path;
	char	*exec_path;


	path = getenv("PATH");
	paths = ft_split(path, ':'); // will not work if path has ' or "

	printf("unknown cmd path:\n");
	while (*paths)
	{
		exec_path = ft_strjoin(*paths, *argv);
		printf("exec path: %s\n", exec_path);
		paths++;
		free(exec_path);
	}
	return (1);
}

char	**create_argv(t_cmd *cmd, int len)
{
	char	**argv;
	char	**argv_cpy;
	int		i;

	argv = malloc(sizeof(char *) * (len + 1));
	argv_cpy = argv;
	i = 0;
	while (i < len)
	{
		*argv_cpy = ft_strdup(cmd->content);
		argv_cpy++;
		i++;
		cmd = cmd->next;
	}
	return (argv);
}

t_cmd	*excecute_cmd(t_minishell *sh, t_cmd *cmd)
{
	t_cmd	*next;
	char	**argv;
	int	builtin_type;
	int	arg_count;

	builtin_type = is_builtin(cmd, cmd->content);
	next = cmd;
	arg_count = 0;
	while (next)
	{
		if (next->type == TYPE_PIPE)
		{
			next = next->next;
			break ;
		}
		arg_count++;
		next = next->next;
	}
	argv = create_argv(cmd, arg_count);
	if (builtin_type)
		excecute_builtin(argv, builtin_type);
	else
		excecute_find(sh, argv);
	ft_free_all(argv);
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
