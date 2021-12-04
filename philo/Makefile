SRC		=	main.c\
			init.c\
			utils/ft_atoi.c\
			utils/ft_isdigit.c\
			utils/my_usleep.c\
			utils/ft_itoa.c\
			utils/ft_strjoin.c\
			utils/ft_strlcat.c\
			utils/ft_strlen.c\
			utils/ft_strlcpy.c\
			validation.c\
			serv_manager.c\
			utils/utils.c\
			life_controller.c

			
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

x		: $(PROG) $(OBJ)
			./philo 1 500 100 100

fclean	:	clean
			rm -f $(PROG)

re		:	fclean all