#include "minishell.h"

void	read_line(char **line_read)
{
	if (*line_read)
	{
		free(*line_read);
		*line_read = (char *)NULL;
	}
	*line_read = readline("minishell> ");
	if (*line_read && **line_read)
		add_history(*line_read);
}
