CC=gcc
CFLAGS=-Wall -Wextra -Werror -g
RM=rm -f
AR=ar -rcs
SRC_PATH=./src/
BUILD_PATH=./build/
FILE_NAMES=memset \
	bzero \
	memcpy \
	memccpy \
	memmove \
	memchr \
	memcmp \
	strlen \
	strlcpy \
	strlcat \
	strchr \
	strrchr \
	strnstr \
	strncmp \
	atoi \
	isalpha \
	isdigit \
	isalnum \
	isascii \
	isprint \
	toupper \
	tolower \
	calloc \
	strdup \
	substr \
	strjoin \
	strtrim \
	split \
	itoa \
	strmapi \
	putchar_fd \
	putstr_fd \
	putendl_fd \
	putnbr_fd
SRC=$(addprefix $(SRC_PATH)ft_, $(addsuffix .c, $(FILE_NAMES)))
OBJ=$(SRC:$(SRC_PATH)%.c=$(BUILD_PATH)%.o)

NAME=libft.a

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $@ $^

$(BUILD_PATH)%.o : $(SRC_PATH)%.c
	$(CC) -I. $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY :
	all clean fclean re
