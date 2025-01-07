NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = ./src/main.c ./src/ft_calloc.c
SRC_DIRS = ./src
OBJS = ${SRCS:.c=.o}

GREEN		=\033[0;32m
RED			=\033[0;31m
BLUE		=\033[0;34m
COLOUR_END	=\033[0m

OBJ_DIR = ./obj
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,${SRCS})

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) -g -c $< -o $@;

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(RED)EVERYTHING COMPILE!$(COLOUR_END)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@${RM} -r ${OBJ_DIR}
	@echo "$(GREEN)EVERYTHING HAS CLEAN!$(COLOUR_END)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)EVERYTHING HAS FCLEAN!$(COLOUR_END)"

re: fclean all
	@$(MAKE)

.PHONY: all clean fclean re