
NAME	=	threads

SRC	=	src/main.c		\

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-W -Wextra -Wall -ggdb3

CPPFLAGS=	-I./include/

all	:	$(OBJ)
		gcc $(CFLAGS) -o $(NAME) $(SRC) $(CPPFLAGS)

clean	:
		rm -f $(OBJ)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
