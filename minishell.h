#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <termios.h>
#include <signal.h>

typedef struct  s_minishell
{
   


} t_minishell;

int     parse(t_minishell *shell, char *line);
void    read_line(char *line_read);
#endif
