#include "minishell.h"



int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_minishell sh;
	(void)sh;
	char		*line;

	sh.envp = copy_envp(envp);
	//sh.envp = envp;
	line = NULL;
	while (1)
	{
		read_line(&line);
		if (parse(&sh, line) == 1)
			continue ;
		handle_cmd(&sh);
	}

	return (0);
}
