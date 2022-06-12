#include "minishell.h"

int	is_builtin(t_cmd *cmd, char *content)
{
	(void)cmd;
	int	i;
	const char	*builtin[BUILTIN_COUNT] = {
		"cd",
		"echo",
		"env",
		"exit",
		"export",
		"pwd",
		"unset"
	};
	const size_t	builtin_len[BUILTIN_COUNT] = {
		2,
		4,
		3,
		4,
		6,
		3,
		5
	};

	i = 0;
	while (i < BUILTIN_COUNT)
	{
		if (!ft_strncmp(builtin[i], content, ft_strlen(content), builtin_len[i]))
			return (i+1);
		i++;
	}
	return 0;

}

int	excecute_builtin(t_minishell *sh, char **argv, int builtin)
{
	// fprintf(stderr,"execute_builtin\n");
	if (builtin == TYPE_CMD_CD)
		cmd_cd(sh, argv);
	else if (builtin == TYPE_CMD_ECHO)
		cmd_echo(sh, argv);
	else if (builtin == TYPE_CMD_ENV)
		cmd_env(sh, argv);
	else if (builtin == TYPE_CMD_EXIT)
		cmd_exit(argv);
	else if (builtin == TYPE_CMD_EXPORT)
		cmd_export(sh, argv);
	else if (builtin == TYPE_CMD_PWD)
		cmd_pwd();
	else if (builtin == TYPE_CMD_UNSET)
		cmd_unset(sh, argv);
	return (0);
}

char	*find_path(char *command)
{
	struct stat	s;
	char		**paths;
	char		*path;
	char		*exec_path;


	if (stat(command, &s) == 0)
		return (ft_strdup(command));
	path = getenv("PATH");
	paths = ft_split(path, ':'); // will not work if path has ' or "
	//fprintf(stderr,"unknown cmd path:\n");
	while (*paths)
	{
		exec_path = ft_strdirjoin(*paths, command);
		//fprintf(stderr,"exec path: %s\n", exec_path);
		paths++;
		if (stat(exec_path, &s) == 0)
			return (exec_path);
		free(exec_path);
	}
	return (NULL);

}

void	excecute_cmd(t_minishell *sh, t_cmd *cmd, int *prev_fds, char *path)
{
	int		builtin_type;
	pid_t	pid;

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
			// fprintf(stderr,"child %d: cmd: %s prev_fds=[%d, %d]\n", pid, cmd->argv[0], prev_fds[0], prev_fds[1]);
			dup2(prev_fds[0], 0);
			ft_close(prev_fds[1]);
			ft_close(prev_fds[0]);
			ft_reset_fd(prev_fds);
		}
		if (cmd->is_left_pipe)
		// if (cmd->is_left_pipe && !(builtin_type && cmd->is_first))
		{
			// fprintf(stderr,"child %d: cmd: %s cmd_fds=[%d, %d]\n", pid, cmd->argv[0], cmd->fds[0], cmd->fds[1]);
			ft_close(cmd->fds[0]);
			if (!(builtin_type && cmd->is_first))
			{
				// fprintf(stderr, "child dup2\n");
				dup2(cmd->fds[1], 1);
			}
			ft_close(cmd->fds[1]);
			ft_reset_fd(cmd->fds);
		}
		if (builtin_type) // if builtin and not first command
		{
			if (!cmd->is_first)
			{
				// fprintf(stderr,"child\n");
				printf("before redirection builtin\n");
				redirection(cmd);
				excecute_builtin(sh, cmd->argv, builtin_type);
			}
		}
		else
		{
			// fprintf(stderr,"hello\n");
			// for(int i=0; i<cmd->arg_count; i++)
				// fprintf(stderr,"%s ", cmd->argv[i]);
			// fprintf(stderr,"\n");
			printf("before redirection bin fuc\n");
			redirection(cmd);
			if (path == NULL)
			{
				ft_error(sh, cmd->argv[0], "command not found", ERR_CMD_NOT_FOUND);
			}
				execve(path, cmd->argv, sh->envp);
//			printf("after execute_bin\n");
		}
//		printf("before child exit\n");
		exit(0);
	}
	else if (pid < 0)
	{
		// error occurred
	}
	else // parent
	{
		sh->pid = pid;
		if (cmd->is_right_pipe)
		{
			//fprintf(stderr,"parent %d: cmd: %s prev_fds=[%d, %d]\n", pid, cmd->argv[0], prev_fds[0], prev_fds[1]);
			ft_close(prev_fds[1]);
			ft_close(prev_fds[0]);
		}
		if (builtin_type && cmd->is_first) // if builtin and first command
		{
			// fprintf(stderr,"parent builtin\n");
			sh->out = dup(0);
			sh->out = dup(1);
			if (cmd->is_left_pipe)
			{
				// fprintf(stderr,"left pipe\n");
				// fprintf(stderr,"parent %d: cmd: %s cmd_fds=[%d, %d]\n", pid, cmd->argv[0], cmd->fds[0], cmd->fds[1]);
				dup2(cmd->fds[1], 1);
				// ft_reset_fd(cmd->fds);
				redirection(cmd);
				excecute_builtin(sh, cmd->argv, builtin_type);
				dup2(sh->out, 0);
				dup2(sh->out, 1);
				close(sh->out);
				return ;
			}
			redirection(cmd);
			excecute_builtin(sh, cmd->argv, builtin_type);
			dup2(sh->out, 1);
			close(sh->out);
		}
	}

	// fprintf(stderr,"pid: %d\n", pid);
	return ;
}

int	handle_cmd(t_minishell *sh)
{
	t_cmd	*cur;
	char	*path;
	int		prev_fds[2];

	ft_reset_fd(prev_fds);
	cur = sh->cmd_list;
	while (cur)
	{
		if (cur->type == TYPE_CMD)
		{
			get_arg_count(cur);
			cur->argv = create_argv(cur, cur->arg_count);
			if (!cur->argv)
				return (0);
		}
		cur = cur->next;
	}
	cur = sh->cmd_list;
	while (cur)
	{
		if (cur->type == TYPE_CMD)
		{
			path = find_path(cur->argv[0]);
			if (path == NULL)
				printf("errno: %d\n", errno);
			excecute_cmd(sh, cur, prev_fds, path);
			if (cur->is_left_pipe)
			{
				prev_fds[0] = cur->fds[0];
				prev_fds[1] = cur->fds[1];
				// fprintf(stderr,"parent %d: cmd: %s prev_fds=[%d, %d]\n", 0, cur->argv[0], prev_fds[0], prev_fds[1]);
			}
			else if (!cur->is_left_pipe)
			{
				//fprintf(stderr, parent %d: cmd: %s cur_fds=[%d, %d]\n", 0, cur->argv[0], cur->fds[0], cur->fds[1]);
				ft_close(cur->fds[0]);
				ft_close(cur->fds[1]);
				ft_reset_fd(cur->fds);
			}
		}
		cur = cur->next;
	}
	//fprintf(stderr,"parent %d: cmd: %s prev_fds=[%d, %d]\n", 0, cur->argv[0], prev_fds[0], prev_fds[1]);
	ft_close(prev_fds[0]);
	ft_close(prev_fds[1]);
	ft_reset_fd(prev_fds);
	ft_lstclear(&sh->cmd_list, free);
	return (1);
}
