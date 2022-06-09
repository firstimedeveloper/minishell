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
	if (builtin == TYPE_CMD_CD)
		return (cmd_cd(sh, argv));
	else if (builtin == TYPE_CMD_ECHO)
		return (cmd_echo(sh->envp, argv));
	else if (builtin == TYPE_CMD_ENV)
		return (cmd_env(sh->envp, argv));//환경변수를 읽어와야해서 변경 argv에서 envp로 파라미터 변경
	else if (builtin == TYPE_CMD_EXIT)
		return (cmd_exit(argv));
	else if (builtin == TYPE_CMD_EXPORT)
		return (cmd_export(sh, argv));
	else if (builtin == TYPE_CMD_PWD)
		return (cmd_pwd(sh->envp, argv));
	else if (builtin == TYPE_CMD_UNSET)
		return (cmd_unset(sh, argv));
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
	exit(1);
	return (1);
}

char	**create_argv(t_cmd *cmd, int len)
{
	char	**argv;
	char	**argv_cpy;
	int		i;

	argv = malloc(sizeof(char *) * (len + 1));
	if (!argv)
		return (0);
	argv_cpy = argv;
	i = 0;
	argv[len] = 0;
	while (i < len)
	{
		*argv_cpy = ft_strdup(cmd->content);
		if (!*argv_cpy)
		{
			return (ft_free_all(argv));
		}
		argv_cpy++;
		i++;
		cmd = cmd->next;
	}
	return (argv);
}

int	excecute_cmd(t_minishell *sh, t_cmd *cmd, int *prev_fds)
{
	int		builtin_type;
	pid_t	pid;
	int		status;

	status = 0;
	builtin_type = is_builtin(cmd, cmd->content);
	if (cmd->is_left_pipe)
	{
		pipe(cmd->fds);
	}
	pid = fork();
	if (pid == 0)
	{
		if (cmd->is_right_pipe)
		{
			//printf("child %d: cmd: %s prev_fds=[%d, %d]\n", pid, cmd->argv[0], prev_fds[0], prev_fds[1]);
			dup2(prev_fds[0], 0);
			ft_close(prev_fds[1]);
			ft_close(prev_fds[0]);
			ft_reset_fd(prev_fds);
		}
		if (cmd->is_left_pipe)
		{
			//printf("child %d: cmd: %s cmd_fds=[%d, %d]\n", pid, cmd->argv[0], cmd->fds[0], cmd->fds[1]);
			ft_close(cmd->fds[0]);
			dup2(cmd->fds[1], 1);
			ft_close(cmd->fds[1]);
			ft_reset_fd(cmd->fds);
		}
		if (builtin_type && cmd->prev) // if builtin and not first command
		{
			printf("child\n");
			excecute_builtin(sh, cmd->argv, builtin_type);
		}
		else
			excecute_find(sh, cmd->argv);
	}
	else if (pid < 0)
	{
		// error occurred
	}
	if (cmd->is_right_pipe)
	{
		//printf("parent %d: cmd: %s prev_fds=[%d, %d]\n", pid, cmd->argv[0], prev_fds[0], prev_fds[1]);
		ft_close(prev_fds[1]);
		ft_close(prev_fds[0]);
	}
	if (builtin_type && !cmd->prev) // if builtin and first command
	{
		printf("parent\n");
		excecute_builtin(sh, cmd->argv, builtin_type);
	}
	waitpid(pid, &status, 0);
	return (status);
}

void	get_arg_count(t_cmd *cmd)
{
	t_cmd	*next;

	next = cmd;
	cmd->arg_count = 0;
	while (next)
	{
		if (next->type == TYPE_PIPE)
		{
			cmd->is_left_pipe = 1;
			next = next->next;
			if (next)
				next->is_right_pipe = 1;
			break ;
		}
		cmd->arg_count++;
		//printf("count: %d\n", cmd->arg_count);
		next = next->next;
	}
}

int	handle_cmd(t_minishell *sh)
{
	t_cmd	*cur;
	int		prev_fds[2];
	//t_cmd	*next;
	// pid_t	pid;
	// int		status;

	// status = 0;
	cur = sh->cmd_list;
	// pid = fork();
	// if (pid == 0)
	// {
		ft_reset_fd(prev_fds);
		while (cur)
		{
			if (cur->type == TYPE_CMD)
			{
				get_arg_count(cur);
				cur->argv = create_argv(cur, cur->arg_count);
				//for (int i=0; i< cur->arg_count; i++)
				//	printf(": %s\n",  cur->argv[i]);
				// if (is_builtin(cur, cur->content) && !cur->is_left_pipe)
				// {
				// 	// for (int i=0; i< cur->arg_count; i++)
				// 	// 	printf("cnt: %d: %s\n", cur->arg_count, cur->argv[i]);
				// 	excecute_builtin(sh, cur->argv, is_builtin(cur, cur->content));
				// }
				// else
				// {
				excecute_cmd(sh, cur, prev_fds);
				if (cur->is_left_pipe)
				{
					prev_fds[0] = cur->fds[0];
					prev_fds[1] = cur->fds[1];
					//printf("parent %d: cmd: %s prev_fds=[%d, %d]\n", 0, cur->argv[0], prev_fds[0], prev_fds[1]);
				}
				else if (!cur->is_left_pipe)
				{
					//printf("parent %d: cmd: %s cur_fds=[%d, %d]\n", 0, cur->argv[0], cur->fds[0], cur->fds[1]);
					ft_close(cur->fds[0]);
					ft_close(cur->fds[1]);
					ft_reset_fd(cur->fds);
				}
				// }
			}
			cur = cur->next;
		}
		//printf("parent %d: cmd: %s prev_fds=[%d, %d]\n", 0, cur->argv[0], prev_fds[0], prev_fds[1]);
		ft_close(prev_fds[0]);
		ft_close(prev_fds[1]);
		ft_reset_fd(prev_fds);
	// }
	// else
	// {
	// 	waitpid(pid, &status, 0);
	// }
	ft_lstclear(&sh->cmd_list, free);
	return (1);
}
