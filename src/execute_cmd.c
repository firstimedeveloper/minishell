/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: san <san@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:53:58 by san               #+#    #+#             */
/*   Updated: 2022/06/16 14:54:03 by san              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			ft_error(cmd->content, NULL, "command not found",
				ERR_CMD_NOT_FOUND);
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

	builtin_type = is_builtin(cmd->content);
	if (cmd->is_left_pipe)
		pipe(cmd->fds);
	pid = fork();
	if (pid == 0)
	{
		child_set_pipe(cmd, prev_fds, builtin_type);
		child_execute(sh, cmd, path, builtin_type);
		exit(g_e_status);
	}
	else if (pid < 0)
	{
		ft_error_open("fork error", 1);
		exit(1);
	}
	else
	{
		sh->pid = pid;
		parent_execute(sh, cmd, prev_fds, builtin_type);
	}
	return ;
}
