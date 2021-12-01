#include "../philo.h"

void	print_message(int phil_number, char *msg, t_table *table, int isFinish)
{
	long long	current_time;

	pthread_mutex_lock(&table->print_pause);
	gettimeofday(&table->time_el, NULL);
	current_time = table->time_el.tv_sec * 1000000 + table->time_el.tv_usec;
	if (isFinish)
		printf("%lld %s\n", (current_time - table->time_start_mcs) / 1000,
		"Everyone finish with meal\n");
	else
		printf("%lld %d %s\n", (current_time - table->time_start_mcs) / 1000,
			phil_number, msg);
	pthread_mutex_unlock(&table->print_pause);
}

void	set_last_time_eat(t_philosopher *philosopher, t_table *table)
{
	struct timeval	time_el;

	gettimeofday(&time_el, NULL);
	philosopher->last_eat_mcs = (time_el.tv_sec * 1000000 + time_el.tv_usec
		- table->time_start_mcs);
}

void exit_routin(t_philosopher_args *args, long long *params, pthread_t *threads)
{
	t_table			*table;
	t_philosopher	*philosophers;
	int				i;

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
	free(table);
	free(philosophers);
	free(threads);
	free(params);
	free(args);
}