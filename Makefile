NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

# READLINE
READLINE_LIB = -lreadline
READLINE_INC = -I/usr/include/readline

# SRCS & OBJS
SRC = src/main.c \
		src/env/init_env.c \
		src/utils/ft_strchr.c \
		src/utils/ft_strchr_ex.c \
		src/utils/ft_strdup.c \
		src/utils/ft_strlen.c \
		src/utils/ft_strndup.c \
		src/utils/ft_memcpy.c \
		src/utils/ft_strcmp.c \
		src/utils/ft_strncmp.c \
		src/utils/ft_strjoin.c \
		src/utils/ft_strjoin_ex.c \
		src/utils/ft_split.c \
		src/utils/ft_atoi.c \
		src/utils/ft_printf.c \
		src/utils/ft_printf_utils.c \
		src/utils/ft_strncat.c \
		src/utils/ft_strtol.c \
		src/utils/ft_getenv.c \
		src/utils/ft_strncpy.c \
		src/utils/ft_env.c \
		src/utils/ft_popnode.c \
		src/input/input.c \
		src/parser/check_quotes.c \
		src/parser/tokenizer.c \
		src/parser/token_utils.c \
		src/parser/tokenize.c \
		src/parser/expand_env.c \
		src/parser/syntax_check.c \
		src/parser/parse_cmd.c	\
		src/exec/exec.c \
		src/exec/exec_utils.c \
		src/exec/error.c \
		src/exec/redir.c \
		src/exec/builtins.c \
		src/exec/builtins_utils.c \
		src/exec/builtins_utils2.c \

OBJS = $(SRC:.c=.o)

# RULES
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(READLINE_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 