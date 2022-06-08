#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <termios.h>
#include <signal.h>
#include <errno.h>

#define TYPE_CMD_CD 1
#define TYPE_CMD_ECHO 2
#define TYPE_CMD_ENV 3
#define TYPE_CMD_EXIT 4
#define TYPE_CMD_EXPORT 5
#define TYPE_CMD_PWD 6
#define TYPE_CMD_UNSET 7

#define TYPE_CMD 0
#define TYPE_ARG 1
#define TYPE_PIPE 2
#define TYPE_REDIR 3

#define MAX 1024

typedef struct s_cmd
{
	int				is_head;
	int				type;
	char			*content;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;


typedef struct  s_minishell
{
	int		in;
	int		out;
	int		e_status;	//exit_status
	char	**envp;
	t_cmd   *cmd_list;

} t_minishell;

int     parse(t_minishell *sh, char *line);
void    read_line(char **line_read);

int	handle_cmd(t_minishell *sh);

/*
*	builtin functions
*/
void	cmd_cd(t_minishell *sh, char **argv);
void	cmd_echo(t_minishell *sh, char **argv);
void	cmd_env(t_minishell *sh, char **argv);
void	cmd_exit(char **argv);
void	cmd_export(t_minishell *sh, char **argv);
void	cmd_pwd(t_minishell *sh);
void	cmd_unset(t_minishell *sh, char **argv);

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
t_cmd	*ft_lstnew(void *content, int type, int is_head);
int	ft_lstsize(t_cmd *lst);

/*
* utils.c
*/
int		ch_strncmp(const char *s1, const char *s2, size_t n);
void	ft_free_double(char **ptr);
int	av_have_eq(char *argv);

/*
* envp_utils.c
*/
int		ft_envplen(char **envp);
int		check_argv_name(t_minishell *sh, char *str, char *cmd);
char	**copy_envp(char **envp);
char	*get_envp_name(char *envp);
char	*ft_getenv(char **envp, char *envp_name);
int		change_envp(char ***envp, char *str);
int		ch_envp_with_name(char ***envp, char *s1, char *s2);

#endif
