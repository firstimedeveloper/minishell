#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <termios.h>
#include <signal.h>

#define TYPE_CMD 0
#define TYPE_ARG 1
#define TYPE_PIPE 2

typedef struct s_cmd
{
	int				is_head;
	int				type;
	char			*content;
	struct s_cmd	*next;
}	t_cmd;


typedef struct  s_minishell
{
	t_cmd   *cmd_list;

} t_minishell;

int     parse(t_minishell *sh, char *line);
void    read_line(char **line_read);

/*
 * util functions
*/
void	ft_lstadd_back(t_cmd **lst, t_cmd *new);
void	ft_lstadd_front(t_cmd **lst, t_cmd *new);
void	ft_lstclear(t_cmd **lst, void (*del)(void *));
void	ft_lstdelone(t_cmd *lst, void (*del)(void *));
void	ft_lstiter(t_cmd *lst, void (*f)(void *));


t_cmd	*ft_lstlast(t_cmd *lst);
t_cmd	*ft_lstmap(t_cmd *lst, void *(*f)(void *), void (*del)(void *));
t_cmd	*ft_lstnew(void *content);
int	ft_lstsize(t_cmd *lst);

#endif
