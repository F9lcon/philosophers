#include "philo.h"

void	print_message(int phil_number, char *msg, t_table *table)
{
	long long	current_all;
	

	if (gettimeofday(&table->time_el, NULL) != 0)
		printf("gettimeofdat in print_message fucked\n");
	current_all = table->time_el.tv_sec * 1000000 + table->time_el.tv_usec;
	printf("%lldms %2d is %s\n", (current_all - table->time_start) / 1000,
			phil_number, msg);
}

void	sleep_philo(t_table *table, t_philosopher *philosopher)
{
	print_message(philosopher->number, "sleeping", table);
	my_usleep(table->time_to_sleep * 1000);
}

void	eat(t_table *table, t_philosopher *philosopher)
{
	pthread_mutex_lock(&(table->forks[philosopher->left_fork]));
	pthread_mutex_lock(&(table->forks[philosopher->right_fork]));
	print_message(philosopher->number, "eating", table);
	my_usleep(table->time_to_eat * 1000);
	pthread_mutex_unlock(&(table->forks[philosopher->left_fork]));
	pthread_mutex_unlock(&(table->forks[philosopher->right_fork]));
	my_usleep(100);
}

void	*routin(void *arg)
{
	t_philosopher_args	*philosopher_args;
	t_philosopher		*philosopher;
	t_table				*table;

	philosopher_args = (t_philosopher_args*) arg;
	philosopher = (t_philosopher*) philosopher_args->philosopher;
	table = (t_table*) philosopher_args->table;
	while (1)
		{
			eat(table, philosopher);
			sleep_philo(table, philosopher);
			print_message(philosopher->number, "thinking", table);
		}
	return (NULL);
}

void	start(long long *params)
{
	pthread_t			threads[params[0]];
	t_philosopher		philosophers[params[0]];
	t_philosopher_args	arguments[params[0]];
	t_table				table; // arr of mutex
	int					i;

	// set arr of philosophers
	table.forks = malloc(params[0] * sizeof(pthread_mutex_t));
	init_philosophers(philosophers, params);
	// set arr of mutex
	init_table(&table, params);
	i = 0;
	while (i < params[0])
	{
		arguments[i].philosopher = &philosophers[i];
		arguments[i].table = &table;
		i++;
	}
	i = 0;
	while (i < params[0])
	{
		if (pthread_create(threads + i, NULL, &routin, arguments + i) != 0)
		{
			printf("thread create fucked\n");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < params[0])
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("thread join fucked\n");
			return ;
		}
		i++;
	}
	destroy_mutex(&table, params);
	return ;
}