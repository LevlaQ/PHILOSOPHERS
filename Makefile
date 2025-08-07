SRCS =	main.c\
		validate_input.c\
		validate_numbers.c\
		calloc.c\
		set_the_table.c\

NAME = philosophers
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror #-fsanitize=address
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