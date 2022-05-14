#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"


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

#endif
