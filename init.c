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

	table->time_to_eat = params[2];
	table->time_to_sleep = params[3];
	pthread_mutex_init(&table->print_pause, NULL);
	if (gettimeofday(&table->time_el, NULL) != 0)
		printf("gettimeofday in init_table fucked\n");
	table->time_start = table->time_el.tv_sec * 1000000
				+ table->time_el.tv_usec;

}

void exit_routin(t_philosopher_args *args, long long *params, pthread_t *threads)
{
	t_table			*table;
	t_philosopher	*philosophers;
	int	i;

	i = 0;
	table = args->table;
	philosophers = args->philosopher;
	while (i < params[0])
	{
		pthread_mutex_destroy(table->forks + i); 
		i++;
	}

	pthread_mutex_destroy(&table->print_pause);
	free(table->forks);
	free(philosophers);
	free(threads);
	free(params);
	free(args);
}


void	init_philosophers(t_philosopher *philosophers,
		long long *params)
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
		i++;
	}
}