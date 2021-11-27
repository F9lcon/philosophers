#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct	s_philosopher
{
	int			number;
	unsigned	left_fork;
	unsigned	right_fork;
	long long	last_eat;
}				t_philosopher;

typedef struct s_fork_data
{
	pthread_mutex_t	mutex;
}					t_fork_data;

typedef struct	s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_pause;
	struct timeval	time_el;
	long long 		time_start;
	long long		time_to_eat;
	long long		time_to_sleep;
}					t_table;

typedef struct	s_philosopher_args
{
	t_table			*table;
	t_philosopher	*philosopher;
}					t_philosopher_args;

void		init_table(t_table *table, long long params[]);
void		exit_routin(t_philosopher_args *args, long long *params, pthread_t *threads);
void		my_usleep(long long microseconds);
int			validation(int argc, char **argv, long long **params);
void		start(long long *params);
long long	ft_atoi(const char *s);
int			ft_isdigit(int c);

// void		init_philosopher(t_philosopher *philosopher, int number,
// 		unsigned left_fork, unsigned right_fork);
void	init_philosophers(t_philosopher *philosophers,
			long long *params);
