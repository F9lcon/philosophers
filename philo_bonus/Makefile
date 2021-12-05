SRC		=	main.c\
			# init.c\
			# utils/ft_atoi.c\
			# utils/ft_isdigit.c\
			# utils/my_usleep.c\
			# utils/ft_itoa.c\
			# utils/ft_strjoin.c\
			# utils/ft_strlcat.c\
			# utils/ft_strlen.c\
			# utils/ft_strlcpy.c\
			# validation.c\
			# serv_manager.c\
			# utils/utils.c\
			# life_controller.c

			
OBJ		=	$(SRC:.c=.o)
PROG	=	philo_bonus
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
HEADER	=	philo_bonus.h

.PHONY	:	all re clean fclean x bonus

all		:	$(PROG)

$(PROG)	:	$(OBJ) Makefile $(HEADER)
			$(CC) $(CFLAGS) $(OBJ) -o $(PROG)

%.o		:	%.c
			$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

clean	:
			rm -f $(OBJ)

x		: $(PROG) $(OBJ)
			./philo 140 410 200 200

fclean	:	clean
			rm -f $(PROG)

re		:	fclean all