NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

GREEN = \033[0;32m
BLUE = \033[0;34m
PURPLE = \033[0;35m
COLOUR_END = \033[0m

OBJ_DIR = ./obj
SRC_DIR = ./src
MAKEFLAGS += -s

INIT = ./src/ft_init.c
ERROR = ./src/ft_error.c
UTILITS = ./src/ft_utilits.c
ACTIONS = ./src/ft_actions.c
ROUTINE = ./src/ft_routine.c
MAIN = ./src/main.c ./src/ft_calloc.c

SRC = $(MAIN) $(ERROR) $(INIT) $(ROUTINE) $(ACTIONS) $(UTILITS)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(PURPLE)EVERYTHING COMPILED!$(COLOUR_END)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)EVERYTHING CLEANED!$(COLOUR_END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)EVERYTHING CLEANED COMPLETELY!$(COLOUR_END)"

re: fclean all
	@$(MAKE)

.PHONY: all clean fclean re