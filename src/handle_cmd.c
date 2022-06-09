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

int	excecute_builtin(t_minishell *sh, char **argv, int builtin)
{
	printf("execute_builtin\n");
	if (builtin == TYPE_CMD_CD)
		cmd_cd(sh, argv);
	else if (builtin == TYPE_CMD_ECHO)
		cmd_echo(sh, argv);
	else if (builtin == TYPE_CMD_ENV)
		cmd_env(sh, argv);
	else if (builtin == TYPE_CMD_EXIT)
		cmd_exit(sh, argv);
	else if (builtin == TYPE_CMD_EXPORT)
		cmd_export(sh, argv);
	else if (builtin == TYPE_CMD_PWD)
		cmd_pwd(sh);
	else if (builtin == TYPE_CMD_UNSET)
		cmd_unset(sh, argv);
	return (0);
}

int	excecute_find(t_minishell *sh, char **argv)
{
	(void)sh;
	char	**paths;
	char	*path;
	char	*exec_path;

	execve(*argv, argv, sh->envp);
	path = getenv("PATH");
	paths = ft_split(path, ':'); // will not work if path has ' or "
	//printf("unknown cmd path:\n");
	while (*paths)
	{
		exec_path = ft_strdirjoin(*paths, *argv);
		//printf("exec path: %s\n", exec_path);
		paths++;
		execve(exec_path, argv, sh->envp);
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
	argv[len] = 0;
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
	int		builtin_type;
	int		arg_count;
	pid_t	pid;
	int		status;
	//int		pipefd[2];

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
		excecute_builtin(sh, argv, builtin_type);
/* 	{
		excecute_builtin(sh, argv, builtin_type);
		exit(0);
	} */
	
	pid = fork();
	if (pid == 0)
	{
		excecute_find(sh, argv);
		ft_free_all(argv);
		exit(0);
	}
	else if (pid < 0)
	{
		// error occurred
	}
	else // parent process
	{
		waitpid(pid, &status, 0);
	}
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
	ft_lstclear(&sh->cmd_list, free);
	return (1);
}
