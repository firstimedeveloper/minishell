#include "minishell.h"

char **copy_envp(char **envp)
{
	char	**ret;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (envp[i++])
		count++;
	ret = malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (0);
	ret[count] = 0;
	i = 0;
	while (i < count)
	{
		ret[i] = ft_strdup(envp[i]);
		i++;
	}
	return (ret);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_minishell sh;
	(void)sh;
	char		*line;

	//sh.envp = copy_envp(envp);
	sh.envp = envp;
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
