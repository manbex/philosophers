NAME = philo

SRC_DIR = srcs/

SRC = main.c ft_superatoi.c

OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))

CC = cc
CFLAGS = -Iincludes
RM = rm -f

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

all: $(NAME)

clean:
	$(RM) $(OBJ) test.o

fclean: clean
	$(RM) $(NAME) test

re: fclean $(NAME)



TEST = test.c

TOBJ = $(TEST:.c=.o)

test: $(TOBJ)
	$(CC) $(TOBJ) -o test



.PHONY: all bonus clean fclean re
