SRCS = 	srcs/main.c \
		srcs/checks.c \
		srcs/init.c \
		srcs/philo_utiles.c \
		srcs/ft_atoi.c \

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3

NAME = philo
O_SRCS = $(SRCS:%.c=%.o)

RM = rm -rf
CC = cc

all: $(NAME)

$(NAME): $(O_SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	$(RM) $(O_SRCS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	@norminette							

.PHONY: all clean fclean re norm
