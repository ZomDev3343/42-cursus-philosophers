SRC=./philo/main.c \
	./philo/time.c \
	./philo/utils.c \
	./philo/control.c \
	./philo/control_2.c \
	./philo/manager.c
OBJ=${SRC:.c=.o}
NAME=philosopher
BONUS_NAME=philosopher_bonus
FLAGS=-Wall -Werror -Wextra -pthread

all: $(NAME)

%.o: %.c
	cc -c $(FLAGS) -g $< -o $@

$(NAME): $(OBJ)
	cc $(FLAGS) $(OBJ) -g -o $(NAME)

clean:
	rm -rf *.o
	rm -rf */*.o

fclean: clean
	rm -rf $(NAME)

re: clean all

.PHONY: all clean fclean re
