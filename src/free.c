#include "minishell.h"

void	ft_free_double(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
	{
		if (ptr[i])
			free(ptr[i]);
	}
	free(ptr);
}

void	ft_free_cmd_list(t_minishell *sh)
{
	t_cmd	*cmd_temp;
	int	i;
i = 0;
	cmd_temp = sh->cmd_list;
	while (cmd_temp)
	{
		printf("cmd_temp %s\n", cmd_temp->argv[0]);


		printf("free %d\n", i++);
		ft_close(cmd_temp->fds[0]);
				printf("free %d\n", i++);

		ft_close(cmd_temp->fds[1]);
				printf("free %d\n", i++);

		if (cmd_temp->content)
			free(cmd_temp->content);
		printf("free %d\n", i++);


		if (cmd_temp->type == TYPE_CMD && cmd_temp->argv[0])
			ft_free_double(cmd_temp->argv);
		printf("free %d\n", i++);

		if (cmd_temp->next)
		{
			printf("here\n");
			cmd_temp = cmd_temp->next;
			free(cmd_temp->prev);
		}
		else
			free(cmd_temp);
		printf("free %d\n", i++);
	}
}

void	ft_exit(int exit_code)
{
	ft_error_open("malloc error", exit_code);
	exit(exit_code);
}

void	ft_free(char *str)
{
	if (str)
		free(str);
}

void	ft_free_cmd_lst(t_minishell *sh)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = sh->cmd_list;
	// if (cur)
	// {
		while (cur)
		{
			next = cur->next;
			fprintf(stderr, "program:\tfreeing %s\n", cur->content);
			free(cur->content);
			if (cur->argv)
				free(cur->argv);
			free(cur);
			cur = next;
		}
		// free(sh->cmd_list);
		sh->cmd_list = NULL;
	// }
}