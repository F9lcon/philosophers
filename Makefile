SRC		=	main.c\
			init.c\
			ft_atoi.c\
			ft_isdigit.c\
			my_usleep.c\
			validation.c\
			ft_lstnew.c\
			ft_lstadd_back.c\
			ft_lstlast.c\
			ft_lstclear.c\
			ft_lstdelone.c\
			start.c\

			
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
			./philo 3 5000 3000 3000

fclean	:	clean
			rm -f $(PROG)

re		:	fclean all