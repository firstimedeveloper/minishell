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
	if (cmd->is_right_pipe)	// cmd 기준 왼쪽에 파이프가 있으면
	{
			// fprintf(stderr,"child %d: cmd: %s prev_fds=[%d, %d]\n", pid, cmd->argv[0], prev_fds[0], prev_fds[1]);
		dup2(prev_fds[0], 0);		// 지금 STDIN의 fds에 이전 커맨드의 fds, 즉 왼쪽 파이프의 fds를 dup2
		ft_close(prev_fds[1]);		// fds 닫기
		ft_close(prev_fds[0]);
		ft_reset_fd(prev_fds);
	}
	if (cmd->is_left_pipe)		// cmd 기준 오른쪽에 파이프가 있으면
	{
		//ft_close(cmd->fds[0]);		// 파이프 다음으로 올 명령어가 인풋( 파이프의 출력)을 받아야하므로 fds를 살려둔다.
		// if (!(builtin_type && cmd->is_first))
		if (!(builtin && cmd->is_first))
			dup2(cmd->fds[1], 1);	// cmd가 처음오는 builtin 명령어가 아니라면 stdout이 파이프로 가도록 dup2
	}
}

// void	child_execute(t_minishell *sh, t_cmd *cmd, char *path, int builtin)
// {

// }

void	excecute_cmd(t_minishell *sh, t_cmd *cmd, int *prev_fds, char *path)
{
	int		builtin_type;
	pid_t	pid;

	builtin_type = is_builtin(cmd, cmd->content);
	if (cmd->is_left_pipe)	// 명령어 기준 오른쪽에 파이프가 있으면
		pipe(cmd->fds);		// pipe() 실행
	pid = fork();			// 포크한다.
	if (pid == 0)			// child 일 때
	{
		//child_set_pipe(cmd, prev_fds, builtin_type);
		if (cmd->is_right_pipe)	// cmd 기준 왼쪽에 파이프가 있으면
		{
			// fprintf(stderr,"child %d: cmd: %s prev_fds=[%d, %d]\n", pid, cmd->argv[0], prev_fds[0], prev_fds[1]);
			dup2(prev_fds[0], 0);		// 지금 STDIN의 fds에 이전 커맨드의 fds, 즉 왼쪽 파이프의 fds를 dup2
			ft_close(prev_fds[1]);		// fds 닫기
			ft_close(prev_fds[0]);
			ft_reset_fd(prev_fds);
		}
		if (cmd->is_left_pipe)		// cmd 기준 오른쪽에 파이프가 있으면
		// if (cmd->is_left_pipe && !(builtin_type && cmd->is_first))
		{
			// fprintf(stderr,"child %d: cmd: %s cmd_fds=[%d, %d]\n", pid, cmd->argv[0], cmd->fds[0], cmd->fds[1]);
			if (!(builtin_type && cmd->is_first))
			{
				dup2(cmd->fds[1], 1);	// cmd가 처음오는 builtin 명령어가 아니라면 stdout이 파이프로 가도록 dup2
			}
			// ft_close(cmd->fds[0]);		// 파이프 다음으로 올 명령어가 인풋( 파이프의 출력)을 받아야하므로 fds를 살려둔다.
			// ft_close(cmd->fds[1]);		// 파이프 다음으로 올 명령어가 인풋( 파이프의 출력)을 받아야하므로 fds를 살려둔다.
			// fprintf(stderr, "%s child dup22\n", cmd->content);

				// output에 다한 fds를 앞으로 쓸일이 없으므로 close
			// fprintf(stderr, "%s child dup23\n", cmd->content);
			//ft_reset_fd(cmd->fds);
		}


		if (builtin_type) // if builtin and not first command
		{
			if (!cmd->is_first)
			{
				redirection(sh, cmd);
				excecute_builtin(sh, cmd->argv, builtin_type);
			}
		}
		else	// bin 함수이면 이쪽으로 온다.
		{
			redirection(sh, cmd);
			if (path == NULL)
			{
				ft_error(cmd->content, NULL, "command not found", ERR_CMD_NOT_FOUND);
				exit(ERR_CMD_NOT_FOUND);
			}
			execve(path, cmd->argv, sh->envp);
		}
		//ft_close(cmd->fds[1]);
		exit(g_e_status);
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
			printf("\n\nclose fds\n\n");
		}
		if (builtin_type && cmd->is_first) // if builtin and first command
		{
			sh->pid = -1;
			// dup2(sh->in, 0);
			// dup2(sh->out, 1);
			if (cmd->is_left_pipe)
			{
				dup2(cmd->fds[1], 1);
				redirection(sh, cmd);
				excecute_builtin(sh, cmd->argv, builtin_type);
				dup2(sh->in, 0);
				dup2(sh->out, 1);
				//close(sh->out);
				return ;
			}
			redirection(sh, cmd);
			excecute_builtin(sh, cmd->argv, builtin_type);
			dup2(sh->out, 1);
		}
	}
	return ;
}

int	handle_cmd(t_minishell *sh)
{
	t_cmd	*cur;
	int		prev_fds[2];

	ft_reset_fd(prev_fds);
	cur = sh->cmd_list;	//다시 처음으로 돌아가서
	while (cur)
	{
		if (cur->type == TYPE_CMD)	// 지금 노드가 명령어면
		{
			init_argv(sh, cur);
			excecute_cmd(sh, cur, prev_fds, cur->path);	// 명령어 수행하는 데로 간다.
			if (cur->is_left_pipe)			// 명령어 기준 오른쪽에 파이프 있으면
			{
				prev_fds[0] = cur->fds[0];	// prev fds 에 현재 cmd의 오른쪽 에 있는 파이프 fds값을 저장한다.
				prev_fds[1] = cur->fds[1];
			}
			else if (!cur->is_left_pipe)	// 이게 필요한지 물어보기
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
	//fprintf(stderr,"parent %d: cmd: %s prev_fds=[%d, %d]\n", 0, cur->argv[0], prev_fds[0], prev_fds[1]);
	// ft_close(prev_fds[0]);
	// ft_close(prev_fds[1]);
	// ft_reset_fd(prev_fds);
	return (0);
}
