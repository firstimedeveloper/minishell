
#include "minishell.h"

int parse(t_minishell *sh, char *line)
{
	char	**split;

	(void)sh;
	split = ft_split(line, ' ');
	while (*split)
	{
		printf("%s ", *split);
		split++;
	}
	printf("\n");
	return 0;
}
