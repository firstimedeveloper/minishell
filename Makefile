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

FILE_NAMES=minishell handle_line parse/parse handle_cmd lst_util1 lst_util2 utils \
builtin/cd builtin/echo builtin/env builtin/exit builtin/export builtin/pwd builtin/unset
SRC=$(addprefix $(SRC_PATH), $(addsuffix .c, $(FILE_NAMES)))
OBJ=$(SRC:$(SRC_PATH)%.c=$(BUILD_PATH)%.o)

NAME=minishell

all: $(NAME)

$(NAME): $(OBJ) $(LIB_PATH)/libft.a
	$(CC) -lreadline $(LIB_PATH)/libft.a $(OBJ) -o $@

$(LIB_PATH)/libft.a:
	make -C libft

$(BUILD_PATH)%.o : $(SRC_PATH)%.c
	$(CC) -I. -c $< -o $@

clean :
	$(RM) $(OBJ)
	@make clean -C $(LIB_PATH)

fclean : clean
	$(RM) $(NAME) libft/libft.a

re : fclean all

.PHONY :
	all clean fclean re

