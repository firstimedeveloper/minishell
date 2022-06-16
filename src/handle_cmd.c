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

char	*find_path(char **envp, char *command)
{
	struct stat	s;
	char		**paths;
	char		**paths_cpy;
	char		*path;

	if (stat(command, &s) == 0)
		return (ft_strdup(command));
	path = ft_getenv(envp, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	free(path);
	paths_cpy = paths;
	while (*paths)
	{
		path = ft_strdirjoin(*paths, command);
		paths++;
		if (stat(path, &s) == 0)
		{
			ft_free_all(paths_cpy);
			return (path);
		}
		free(path);
	}
	ft_free_all(paths_cpy);
	return (NULL);
}

void	child_set_pipe(t_cmd *cmd, int *prev_fds, int builtin)
{
	if (cmd->is_right_pipe)
	{
		dup2(prev_fds[0], 0);
		ft_close(prev_fds[1]);
		ft_close(prev_fds[0]);
		ft_reset_fd(prev_fds);
	}
	if (cmd->is_left_pipe)
	{
		if (!(builtin && cmd->is_first))
			dup2(cmd->fds[1], 1);
	}
}

void	child_execute(t_minishell *sh, t_cmd *cmd, char *path, int builtin)
{
	if (builtin)
	{
		if (!cmd->is_first)
		{
			redirection(sh, cmd);
			excecute_builtin(sh, cmd->argv, builtin);
		}
	}
	else
	{
		redirection(sh, cmd);
		if (path == NULL)
		{
			ft_error(cmd->content, NULL, "command not found", ERR_CMD_NOT_FOUND);
			exit(ERR_CMD_NOT_FOUND);
		}
		execve(path, cmd->argv, sh->envp);
	}
}

void	parent_execute(t_minishell *sh, t_cmd *cmd, int *prev_fds, int builtin)
{
	if (cmd->is_right_pipe)
		{
			ft_close(prev_fds[1]);
			ft_close(prev_fds[0]);
		}
		if (builtin && cmd->is_first)
		{
			sh->pid = -1;
			if (cmd->is_left_pipe)
			{
				dup2(cmd->fds[1], 1);
				redirection(sh, cmd);
				excecute_builtin(sh, cmd->argv, builtin);
				dup2(sh->in, 0);
				dup2(sh->out, 1);
				return ;
			}
			redirection(sh, cmd);
			excecute_builtin(sh, cmd->argv, builtin);
			dup2(sh->out, 1);
		}
}

void	excecute_cmd(t_minishell *sh, t_cmd *cmd, int *prev_fds, char *path)
{
	int		builtin_type;
	pid_t	pid;

	builtin_type = is_builtin(cmd, cmd->content);
	if (cmd->is_left_pipe)
		pipe(cmd->fds);
	pid = fork();
	if (pid == 0)
	{
		child_set_pipe(cmd, prev_fds, builtin_type);
		// if (cmd->is_right_pipe)
		// {
		// 	dup2(prev_fds[0], 0);
		// 	ft_close(prev_fds[1]);
		// 	ft_close(prev_fds[0]);
		// 	ft_reset_fd(prev_fds);
		// }
		// if (cmd->is_left_pipe)
		// {
		// 	if (!(builtin_type && cmd->is_first))
		// 		dup2(cmd->fds[1], 1);
		// }

		child_execute(sh, cmd, path, builtin_type);
		// if (builtin_type)
		// {
		// 	if (!cmd->is_first)
		// 	{
		// 		redirection(sh, cmd);
		// 		excecute_builtin(sh, cmd->argv, builtin_type);
		// 	}
		// }
		// else
		// {
		// 	redirection(sh, cmd);
		// 	if (path == NULL)
		// 	{
		// 		ft_error(cmd->content, NULL, "command not found", ERR_CMD_NOT_FOUND);
		// 		exit(ERR_CMD_NOT_FOUND);
		// 	}
		// 	execve(path, cmd->argv, sh->envp);
		// }
		exit(g_e_status);
	}
	else if (pid < 0)
	{
		// error occurred
	}
	else
	{
		sh->pid = pid;
		parent_execute(sh, cmd, prev_fds, builtin_type);
		// if (cmd->is_right_pipe)
		// {
		// 	ft_close(prev_fds[1]);
		// 	ft_close(prev_fds[0]);
		// }
		// if (builtin_type && cmd->is_first)
		// {
		// 	sh->pid = -1;
		// 	if (cmd->is_left_pipe)
		// 	{
		// 		dup2(cmd->fds[1], 1);
		// 		redirection(sh, cmd);
		// 		excecute_builtin(sh, cmd->argv, builtin_type);
		// 		dup2(sh->in, 0);
		// 		dup2(sh->out, 1);
		// 		return ;
		// 	}
		// 	redirection(sh, cmd);
		// 	excecute_builtin(sh, cmd->argv, builtin_type);
		// 	dup2(sh->out, 1);
		// }
	}
	return ;
}

int	handle_cmd(t_minishell *sh)
{
	t_cmd	*cur;
	int		prev_fds[2];

	ft_reset_fd(prev_fds);
	cur = sh->cmd_list;
	while (cur)
	{
		if (cur->type == TYPE_CMD)
		{
			init_argv(sh, cur);
			excecute_cmd(sh, cur, prev_fds, cur->path);
			if (cur->is_left_pipe)
			{
				prev_fds[0] = cur->fds[0];
				prev_fds[1] = cur->fds[1];
			}
			else if (!cur->is_left_pipe)
			{
				ft_close(cur->fds[0]);
				ft_close(cur->fds[1]);
				ft_reset_fd(cur->fds);
			}
			if (!is_builtin(cur, cur->content))
				ft_free(cur->path);
		}
		cur = cur->next;
	}
	return (0);
}
