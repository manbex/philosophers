NAME	=	philo

INC_DIR	=	includes/
INC		=	$(addprefix $(INC_DIR),	\
			philo.h					\
			)

SRC_DIR	=	srcs/
SRC		= 	main.c					\
			init.c					\
			philo.c					\
			ft_superatoi.c			\
			utils.c					\

OBJ_DIR	=	obj/
OBJ		=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC		=	cc
CFLAGS	=	-Iincludes -pthread -Wall -Wextra -Werror
RM		=	rm -f

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(INC)
					@mkdir -p $(@D)
					$(CC) $(CFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
					$(CC) $(CFLAGS) $(OBJ) -o $@

all:			$(NAME)

clean:
					$(RM) -r $(OBJ_DIR) test.o

fclean:	clean
					$(RM) $(NAME) test

re:				fclean $(NAME)

.PHONY: 		all bonus clean fclean re
