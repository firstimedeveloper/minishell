
#include "minishell.h"

int parse(t_minishell *sh, char *line)
{
	char	**split;
	char	**split_cpy;

	(void)sh;
	split = ft_split(line, ' ');
	split_cpy = split;
	while (*split)
	{
		printf("%s ", *split);
		split++;
	}
	printf("\n");
	return 0;
}
