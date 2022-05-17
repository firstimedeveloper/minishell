#include "minishell.h"

t_cmd	*ft_lstlast(t_cmd *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

// t_cmd	*ft_lstmap(t_cmd *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_cmd	*new_lst;
// 	t_cmd	*temp;

// 	new_lst = 0;
// 	while (lst)
// 	{
// 		temp = ft_lstnew(f(lst->content));
// 		if (!temp)
// 		{
// 			ft_lstclear(&new_lst, del);
// 			return (0);
// 		}
// 		ft_lstadd_back(&new_lst, temp);
// 		lst = lst->next;
// 	}
// 	return (new_lst);
// }

t_cmd	*ft_lstnew(void *content, int type, int is_head)
{
	t_cmd	*ret;

	ret = malloc(sizeof(t_cmd));
	if (!ret)
		return (0);
	ret->content = content;
	ret->type = type;
	ret->is_head = is_head;
	ret->next = 0;
	ret->prev = 0;
	return (ret);
}

int	ft_lstsize(t_cmd *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
