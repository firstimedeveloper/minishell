# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juhan <juhan@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/15 15:47:16 by juhan             #+#    #+#              #
#    Updated: 2022/05/14 16:28:23 by juhan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -Wall -Werror -Wextra
LIB_PATH=libft
SRC_PATH=./src/
BUILD_PATH=./build/
#READLINE_LIB 	= -lreadline -L/usr/local/opt/readline/lib
#READLINE_INC	= -I/usr/local/opt/readline/includeBUILD_PATH=./build/

READLINE_LIB	= -lreadline -L/opt/homebrew/opt/readline/lib
READLINE_INC	= -I/opt/homebrew/opt/readline/include

FILE_NAMES=minishell handle_line parse/parse parse/init_argv handle_cmd lst_util1 lst_util2 utils envp_utils1 envp_utils2 signal \
builtin/cd builtin/echo builtin/env builtin/exit builtin/export builtin/pwd builtin/unset \
execute redirection utils/stack_util1 parse/expansion

SRC=$(addprefix $(SRC_PATH), $(addsuffix .c, $(FILE_NAMES)))
OBJ=$(SRC:$(SRC_PATH)%.c=$(BUILD_PATH)%.o)

NAME=minishell

all: $(NAME)

$(NAME): $(OBJ) $(LIB_PATH)/libft.a
	$(CC) $(READLINE_LIB) $(READLINE_INC) $(LIB_PATH)/libft.a $(OBJ) -o $@

$(LIB_PATH)/libft.a:
	make -C libft

$(BUILD_PATH)%.o : $(SRC_PATH)%.c
	$(CC) -I. $(READLINE_INC) -c $< -o $@

clean :
	$(RM) $(OBJ)
	@make clean -C $(LIB_PATH)

fclean : clean
	$(RM) $(NAME) libft/libft.a

re : fclean all

.PHONY :
	all clean fclean re

