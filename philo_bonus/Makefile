SRCS = 	srcs/main.c \
		srcs/check.c \
		srcs/init.c \
		srcs/ft_atoi.c \
		srcs/philo_utiles.c \
# CFLAGS = -Wall -Wextra -Werror

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