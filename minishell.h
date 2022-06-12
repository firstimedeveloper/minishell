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
#include <sys/wait.h>
#include <fcntl.h> // open
#include <sys/types.h>
#include <sys/stat.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define BUILTIN_COUNT 7

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
#define TYPE_REDIR_INPUT 3
#define TYPE_REDIR_OUTPUT 4
#define TYPE_REDIR_APPEND 5
#define TYPE_REDIR_HEREDOC 6

#define ERR_CMD_NOT_FOUND 127

#define NO_PIPE 0
#define PIPE_LEFT 1
#define PIPE_RIGHT 2
#define PIPE_BOTH 3
#define MAX 1024

#define CHAR_NO_QUOTE 0
#define CHAR_SINGLE_QUOTE 1
#define CHAR_DOUBLE_QUOTE 2

typedef struct s_stack
{
	int	top;
	int	items[MAX];
}	t_stack;

typedef struct s_cmd
{
	int				is_head;
	int				type;
	int				fds[2];
	int				is_first;
	int				redir_in;
	int				redir_out;
	int				is_left_pipe;
	int				is_right_pipe;
	int				arg_count;
	char			*content;
	char			**argv;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;


typedef struct  s_minishell
{
	pid_t			pid;
	int		in;
	int		out;
	char	**envp;
	t_cmd   *cmd_list;

} t_minishell;

int	g_e_status;

/*
*	parse functions
*/

char	**create_argv(t_cmd *cmd, int len);
void	get_arg_count(t_cmd *cmd);
char	*handle_expansion(t_minishell *sh, char *str);
int		parse(t_minishell *sh, char *line);
void	read_line(char **line_read);

int	handle_cmd(t_minishell *sh);

/*
*	builtin functions
*/
void	cmd_cd(t_minishell *sh, char **argv);
void	cmd_echo(t_minishell *sh, char **argv);
void	cmd_env(t_minishell *sh, char **argv);
void	cmd_exit(char **argv);
void	cmd_export(t_minishell *sh, char **argv);
void	cmd_pwd();
void	cmd_unset(t_minishell *sh, char **argv);

/*
* list util functions
*/
void	ft_lstadd_back(t_cmd **lst, t_cmd *new);
void	ft_lstadd_front(t_cmd **lst, t_cmd *new);
void	ft_lstclear(t_cmd **lst, void (*del)(void *));
void	ft_lstdelone(t_cmd *lst, void (*del)(void *));
void	ft_lstiter(t_cmd *lst, void (*f)(void *));


t_cmd	*ft_lstlast(t_cmd *lst);
t_cmd	*ft_lstmap(t_cmd *lst, void *(*f)(void *), void (*del)(void *));
t_cmd	*ft_lstnew(void *content, int type, int is_head, int is_first);
int		ft_lstsize(t_cmd *lst);

/*
*	utils
*/
int			ch_strncmp(const char *s1, const char *s2, size_t n);
void		ft_free_double(char **ptr);
int			av_have_eq(char *argv);
int			av_have_eq(char *argv);
long long	ft_atoll(const char *str);

/*
*	envp_util functions
*/
int		ft_envplen(char **envp);
int		check_argv_name(char *str, char *cmd);
char	**copy_envp(char **envp);
char	*get_envp_name(char *envp);
char	*ft_getenv(char **envp, char *envp_name);
void	change_envp(char ***envp, char *str);
int		ch_envp_with_name(char ***envp, char *s1, char *s2);

/*
* signal.c
*/
void	ft_signal_handler(int signo);

/*
redirection
 */
t_cmd	*redirection(t_minishell *sh, t_cmd *cmd);


/*
free.c
 */
void	ft_free_double(char **ptr);
void	ft_free_cmd_list(t_minishell *sh);
void	ft_exit(t_minishell *sh, int exit_code);

/*
ft_error.c
 */
void	ft_error(char *command, char *argv, char *err_msg, int err_code);
void	ft_error_2(char *command, char *argv, int err_code);
void	ft_error_redir(char *err_msg, int err_code, int fd);
void	ft_error_open(char *err_msg, int err_code);




void	ft_reset_fd(int *fd);
void	ft_close(int fd);

void	read_line_heredoc(char **line_read);


#endif
