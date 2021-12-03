#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct	s_philosopher
{
	int				number;
	unsigned		left_fork;
	unsigned		right_fork;
	long long		last_eat_mcs;
	int				can_eat;
}				t_philosopher;

typedef struct s_fork_data
{
	pthread_mutex_t	mutex;
}					t_fork_data;

typedef struct	s_table
{
	pthread_mutex_t	*forks;
	int				number_of_philo;
	int				times_to_eat;
	pthread_mutex_t	print_pause;
	struct timeval	time_el;
	int				all_alive;
	long long 		time_start_mcs;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	pthread_t		*threads;
}					t_table;

typedef struct	s_philosopher_args
{
	t_table			*table;
	t_philosopher	*philosopher;
}					t_philosopher_args;

void		detach_thread(t_philosopher_args* arguments);
void		*life_controller_thread(void *arg);
void		init_table(t_table *table, int params[]);
void		exit_routin(t_philosopher_args *args, int *params, pthread_t *threads);
void		my_usleep(int microseconds);
int			validation(int argc, char **argv, int **params);
void		serv_manager(int *params);
void		life_controller(t_philosopher_args* arguments);
void		set_last_time_eat(t_philosopher *philosopher, t_table *table);
long long	ft_atoi(const char *s);
int			ft_isdigit(int c);
void		print_message(int phil_number, char *msg, t_table *table, int isFinish);
t_philosopher_args	*create_args(int *params);
// void		init_philosopher(t_philosopher *philosopher, int number,
// 		unsigned left_fork, unsigned right_fork);
			
