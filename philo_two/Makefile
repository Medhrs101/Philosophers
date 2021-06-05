NAME = philo_two
LIB = philo_two.a
SRC =./philo_two.c \
	./get_and_check_args.c \
	./utils.c \
	./eating_dying.c


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