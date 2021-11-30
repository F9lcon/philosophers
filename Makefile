SRC		=	main.c\
			init.c\
			ft_atoi.c\
			ft_isdigit.c\
			my_usleep.c\
			validation.c\
			start.c\
			utils.c

			
OBJ		=	$(SRC:.c=.o)
PROG	=	philo
# LIB		=	$(LIBDIR)/libft.a
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g -pthread
HEADER	=	philo.h

.PHONY	:	all re clean fclean x

all		:	$(PROG)


$(PROG)	:	$(OBJ) Makefile $(HEADER)
			$(CC) $(CFLAGS) $(OBJ) -o $(PROG)

%.o		:	%.c
			$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean	:
			rm -f $(OBJ)

x		: $(PROG) $(OBJ) Makefile $(HEADER)
			./philo 4 410 200 200 1

fclean	:	clean
			rm -f $(PROG)

re		:	fclean all