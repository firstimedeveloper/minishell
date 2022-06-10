#include "minishell.h"

void	handle_cmd_type(char *s, int is_head, int *type)
{
	if (is_head)
		*type = TYPE_CMD;
	else if (*s == '|')
		*type = TYPE_PIPE;
	else if (*s == '<')
	{
		*type = TYPE_REDIR_INPUT;
		if (*(s+1) && *(s+1) == '<')
			*type = TYPE_REDIR_APPEND;
	}
	else if (*s == '>')
	{
		*type = TYPE_REDIR_OUTPUT;
		if (*(s+1) && *(s+1) == '>')
			*type = TYPE_REDIR_APPEND;
	}
	else
		*type = TYPE_ARG;
}

int parse(t_minishell *sh, char *line)
{
	t_cmd	*cur;
	t_cmd	*tmp;
	char	**split;
	int		is_head;
	int		type;

	is_head = 1;
	split = ft_split(line, ' ');
	if (!split || !*split)
		return (1);
	//printf("%s ", *split);
	cur = ft_lstnew(*split++, TYPE_CMD, is_head);
	sh->cmd_list = cur;
	while (*split)
	{
		if (cur->type == TYPE_PIPE)
			is_head = 1;
		else
			is_head = 0;
		handle_cmd_type(*split, is_head, &type);
//	printf("\n %s: handle_cmd_type %d\n", *split, type);

		tmp = ft_lstnew(*split, type, is_head);
		if (!tmp)
			return 1; //임시
		tmp->is_first = 0;
		ft_lstadd_back(&sh->cmd_list, tmp);
		//printf("%s ", *split);
		split++;
		cur = cur->next;
	}
	return 0;
}
