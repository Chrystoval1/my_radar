##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## automation if compilation/commands
##

SRC 	=	src/my_radar.c\
		src/parse.c\
		src/diplay.c\
		src/movement.c\
		utils/my_strcmp.c\
		utils/my_getnbr.c\

OBJ	=	$(SRC:.c=.o)

NAME	=	my_radar

FLAGS	=	-g
CFLAGS	+=	$(FLAGS)

all:	$(NAME)

$(NAME):	$(OBJ)
	cd ./printf && make re
	gcc -o $(NAME) $(FLAGS) $(SRC) -L./printf/ -lmy\
	    -lcsfml-graphics -lcsfml-window -lcsfml-system -lm

clean:
	rm -f $(OBJ)
fclean: clean
	cd printf/ && make fclean
	rm -f $(NAME)
re:	fclean all
