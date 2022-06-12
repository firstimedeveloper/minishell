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

void	ft_error(t_minishell *sh, char *command, char *err_msg, int err_code)
{
	(void)sh;
	(void)err_code;
	printf("minishell: %s: %s\n", command, err_msg);
	// if (err_code != 0)
		//g_e_status = err_code;
}

void	excecute_cmd(t_minishell *sh, t_cmd *cmd, int *prev_fds, char *path)
{
	int		builtin_type;
	pid_t	pid;

	builtin_type = is_builtin(cmd, cmd->content);
	// fprintf(stderr, "%s builintype : %d\n", cmd->content, builtin_type);
	if (cmd->is_left_pipe)	// 명령어 기준 오른쪽에 파이프가 있으면 
	{
		pipe(cmd->fds);		// pipe() 실행
	}
	pid = fork();			// 포크한다.
	if (pid == 0)			// child 일 때 
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
		// if (cmd->is_left_pipe && !(builtin_type && cmd->is_first))
		{
			// fprintf(stderr,"child %d: cmd: %s cmd_fds=[%d, %d]\n", pid, cmd->argv[0], cmd->fds[0], cmd->fds[1]);
			//ft_close(cmd->fds[0]);		// 파이프 다음으로 올 명령어가 인풋을 받아야하므로 fds를 살려둔다. 
			if (!(builtin_type && cmd->is_first))
			{
				dup2(cmd->fds[1], 1);	// cmd가 처음오는 builtin 명령어가 아니라면 stdout이 파이프로 가도록 dup2
			}
			// fprintf(stderr, "%s child dup22\n", cmd->content);

				// output에 다한 fds를 앞으로 쓸일이 없으므로 close
			// fprintf(stderr, "%s child dup23\n", cmd->content);
			//ft_reset_fd(cmd->fds);
		}

//////////////여기 주석 달아야함 
		if (builtin_type) // if builtin and not first command
		{
			if (!cmd->is_first)
			{
				// fprintf(stderr,"child builtin and is not first cmd\n\n");
				redirection(sh, cmd);
				excecute_builtin(sh, cmd->argv, builtin_type);
			}
		}
		else	// bin 함수이면 이쪽으로 온다. 
		{			
			// fprintf(stderr, "%s child dup24\n", cmd->content);
			redirection(sh, cmd);
			// fprintf(stderr, "%s after redirection\n", cmd->content);

			if (path == NULL)
			{
				ft_error(sh, cmd->argv[0], "command not found", ERR_CMD_NOT_FOUND);
				exit(ERR_CMD_NOT_FOUND);
			}
			execve(path, cmd->argv, sh->envp);
//			printf("after execute_bin\n");
		}
//		printf("before child exit\n");
		ft_close(cmd->fds[1]);
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
				redirection(sh, cmd);
				excecute_builtin(sh, cmd->argv, builtin_type);
				dup2(sh->out, 0);
				dup2(sh->out, 1);
				close(sh->out);
				return ;
			}
			redirection(sh, cmd);
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
			// fprintf(stderr, "%s is left pipe : %d\n", cur->content, cur->is_left_pipe);
			// fprintf(stderr, "%s is right pipe : %d\n\n", cur->content, cur->is_right_pipe);
		}
		cur = cur->next;
	}
	cur = sh->cmd_list;	//다시 처음으로 돌아가서 
	while (cur)
	{
		if (cur->type == TYPE_CMD)	// 지금 노드가 명령어면 
		{
			path = find_path(cur->argv[0]);	// 명령어의 위치를 찾고 
			if (path == NULL)				//없으면 에러 메세지 ////////////////빌트인일 떄는?
				printf("errno: %d\n", errno);

			// fprintf(stderr,"handle_cmd : cmd: %s prev_fds=[%d, %d]\n\n", cur->content, prev_fds[0], prev_fds[1]);

			excecute_cmd(sh, cur, prev_fds, path);	// 명령어 수행하는 데로 간다. 

			// 명령어 수행하고 나서 
			if (cur->is_left_pipe)			// 명령어 기준 오른쪽에 파이프 있으면 
			{
				prev_fds[0] = cur->fds[0];	// prev fds 에 현재 cmd의 오른쪽 에 있는 파이프 fds값을 저장한다. 
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
