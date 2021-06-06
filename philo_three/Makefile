NAME = philo_three
LIB = philo_three.a
SRC =./philo_three.c \
	./eating_dying.c \
	./get_and_check_args.c \
	./semaphore.c \
	./utils.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJ) 
	ar rcs $(LIB) $(OBJ)
	gcc  $(FLAGS) $(LIB) -o $(NAME)

%.o: %.c
	gcc $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ) $(LIB)

fclean: clean
	@rm -f $(NAME)

re: fclean all