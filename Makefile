SRC=philo/main.c \
	philo/ft_atoi.c \
	time.c
OBJ=${SRC:.c=.o}
NAME=philo
BONUS_NAME=philo_bonus
FLAGS=-Wall -Werror -Wextra

all: $(NAME)

%.o: %.c
	cc -c $(FLAGS) -g $< -o $@

$(NAME): $(OBJ)
	cc $(FLAGS) $(LIBS) -g -o $(NAME)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all clean fclean re
