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
	else if (*line_read == NULL)
	{
		printf("\033[1A"); // 커서를 위로 한 줄 올린다.	
		printf("\033[11C"); // 커서를 10만큼 앞으로 전진시킨다.
		printf("exit\n");
		free(*line_read);
		exit(0);
	}
}

void	read_line_heredoc(char **line_read)
{
	// if (*line_read)
	// {
	// 	free(*line_read);
	// 	*line_read = (char *)NULL;
	// }
	fprintf(stderr, "before readline\n");
	*line_read = readline("> ");
		fprintf(stderr, "after readline\n");

	if (*line_read == NULL)
	{
		//입력받은거 출력하기 
		printf("put ctrl D\n");
		free(*line_read);
		exit(0);
	}
}