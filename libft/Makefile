CC=gcc
CFLAGS=-Wall -Wextra -Werror
RM=rm -f
AR=ar -rcs
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

SRCS=$(addprefix ft_, $(addsuffix .c, $(FILE_NAMES)))

OBJS=$(SRCS:.c=.o)
INCLUDES=libft.h
NAME=libft.a

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY :
	all clean fclean re
