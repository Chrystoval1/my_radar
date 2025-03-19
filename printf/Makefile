##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## automation if compilation/commands
##

SRC 	=	my_printf.c\
		handle_basic.c\
		convertions.c\
		my_putchar.c\
		my_strlen.c\
		my_put_nbr.c\
    my_putstr.c\
    my_compute_power_rec_long.c\
    my_put_nbr_long.c\
    my_put_float.c\


OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re:	fclean	 all
