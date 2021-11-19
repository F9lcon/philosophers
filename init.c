#include "philo.h"

void	init_table(t_table *table, long long params[])
{
	int	i;

	i = 0;
	while (i < params[0])
	{
		pthread_mutex_init(table->forks + i, NULL);
		i++;
	}
	if (gettimeofday(&table->time_el, NULL) != 0)
		printf("gettimeofday in init_table fucked\n");
	table->time_start = table->time_el.tv_sec * 1000000 + table->time_el.tv_usec;
	table->time_to_eat = params[2];
	table->time_to_sleep = params[3];
}

void destroy_mutex(t_table *table, long long params[])
{
	int	i;

	i = 0;
	while (i < params[0])
	{
		pthread_mutex_destroy(table->forks + i);
		i++;
	}
	free(table->forks);
}

// void init_philosopher(t_philosopher *philosopher, int number,
// 		unsigned left_fork, unsigned right_fork)

void	init_philosophers(t_philosopher *philosophers, long long *params)
{
	int	i;

	i = 0;
	while (i < params[0])
	{
		(&philosophers[i])->number = i + 1;
		(&philosophers[i])->left_fork = i;
		if (i + 1 == params[0])
			(&philosophers[i])->right_fork = 0;
		else
			(&philosophers[i])->right_fork = i + 1;
		printf("philo %d left %d right %d\n", (&philosophers[i])->number,
		(&philosophers[i])->left_fork,
		(&philosophers[i])->right_fork);
		i++;
	}


	// philosopher->number = number;
	// philosopher->left_fork = left_fork;
	// philosopher->right_fork = right_fork;
}