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
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_die;
	pthread_t		*threads;
}					t_table;

typedef struct	s_philosopher_args
{
	t_table			*table;
	t_philosopher	*philosopher;
}					t_philosopher_args;

void		detach_thread(t_philosopher_args* arguments);
void		*waiter_routing(void *arg);
void		init_table(t_table *table, long long params[]);
void		exit_routin(t_philosopher_args *args, long long *params, pthread_t *threads);
void		my_usleep(long long microseconds);
int			validation(int argc, char **argv, long long **params);
void		serv_manager(long long *params);
void		waiter_start(t_philosopher_args* arguments);
void		set_last_time_eat(t_philosopher *philosopher, t_table *table);
long long	ft_atoi(const char *s);
int			ft_isdigit(int c);
void		print_message(int phil_number, char *msg, t_table *table);
t_philosopher_args	*create_args(long long *params);
// void		init_philosopher(t_philosopher *philosopher, int number,
// 		unsigned left_fork, unsigned right_fork);
			
