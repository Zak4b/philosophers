NAME = philo

GREEN = \033[32m
RED = \033[31m
YELLOW = \033[0;33m
RESET = \033[0m

FLAGS = -Wall -Wextra -Werror -g

SOURCES = \
        main.c \
		philo.c \
		utils.c

OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(GREEN)Compiling $(NAME)...$(RESET)"
	@cc $(FLAGS) $(OBJS) -o $(NAME) $(INC) $(LIB)
	@echo "$(GREEN)Compilation finished successfully!$(RESET)"

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@cc $(FLAGS) $(INC) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo "$(RED)Cleaning all...$(RESET)"
	@rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
