#include "minishell.h"

void	ft_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*cur;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	cur = *lst;
	while (cur && cur->next)
		cur = cur->next;
	new->prev = cur;
	cur->next = new;
}

void	ft_lstadd_front(t_cmd **lst, t_cmd *new)
{
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

void	ft_lstclear(t_cmd **lst, void (*del)(void *))
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = *lst;
	while (cur)
	{
		next = cur->next;
		ft_lstdelone(cur, del);
		cur = next;
	}
	*lst = 0;
}

void	ft_lstdelone(t_cmd *lst, void (*del)(void *))
{
	if (lst->content)
		del(lst->content);
	free(lst);
}

void	ft_lstiter(t_cmd *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

