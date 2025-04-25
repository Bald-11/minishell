NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFLAGS = -lreadline -lhistory

RESET = \033[0m
BOLD = \033[1m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m

SRC_FILES = main.c input.c utils.c utils2.c utils3.c utils4.c tokens.c tokenizer.c tokenizer2.c \
			parser.c parser2.c redir.c cmds.c exec.c ft_split.c builtins.c error.c exec_utils.c \
			exec_utils2.c exec_utils3.c builtins2.c utils5.c

SRC = $(addprefix src/, $(SRC_FILES))
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(BOLD)$(BLUE)🔨 Building $(NAME)...$(RESET)"
	@$(CC) $(OBJ) $(LIBFLAGS) -o $(NAME)
	@echo "$(BOLD)$(GREEN)✅ Build successful! $(NAME) is ready.$(RESET)"

%.o: %.c
	@echo "$(YELLOW)🔄 Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(MAGENTA)🧹 Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(GREEN)✨ Cleanup complete!$(RESET)"

fclean: 
	@echo "$(MAGENTA)🧹 Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@echo "$(GREEN)✨ Deep cleanup complete!$(RESET)"

re: fclean all
	@echo "$(CYAN)♻️  Project rebuilt from scratch!$(RESET)"

.PHONY: clean fclean re all