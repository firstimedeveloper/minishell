#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <termios.h>
#include <signal.h>

typedef struct s_cmd
{
    char    *cmd;
    char    *str;
    int     flag;
    struct s_cmd    *prev;
    struct s_cmd    *next;
}               t_cmd;

typedef struct  s_minishell
{
    int temp;
    t_cmd   *cmd_list;

} t_minishell;

int     parse(t_minishell *sh, char *line);
void    read_line(char **line_read);
#endif
