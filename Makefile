NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -lreadline -lhistory

RESET = \033[0m
BOLD = \033[1m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m

SRC_FILES = main.c
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