SRCS = 	srcs/main.c \
		includes/libft/ft_atoi.c \

# CFLAGS = -Wall -Wextra -Werror
NAME = philo
O_SRCS = $(SRCS:%.c=%.o)

RM = rm -rf
CC = cc

all: $(NAME)

$(NAME): $(O_SRCS)
	$(CC) $(CFLAGS) $(SRCS) -pthread -o $(NAME)

clean:
	$(RM) $(O_SRCS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	@norminette

.PHONY: all clean fclean re norm