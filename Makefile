SRC		=	main.c 
OBJ		=	$(SRC:.c=.o)
PROG	=	philo
# LIB		=	$(LIBDIR)/libft.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g -pthread
# HEADER	=	minishell.h

.PHONY	:	all re clean fclean x

all		:	$(PROG)


$(PROG)	:	$(OBJ) Makefile
			$(CC) $(CFLAGS) $(OBJ) -o $(PROG)

%.o		:	%.c
			$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean	:
			rm -f $(OBJ)

x		: all
			./philo

fclean	:	clean
			rm -f $(PROG)

re		:	fclean all