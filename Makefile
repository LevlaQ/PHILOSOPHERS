SRCS =	main.c\
		validate_input.c\
		set_the_table.c\
		philo_utils.c\
		life_cycle.c\
		free_funcitons.c\
		waitress.c\

NAME = philo
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror -fsanitize=undefined
OBJS = $(SRCS:.c=.o)
FLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(FLAGS)

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re