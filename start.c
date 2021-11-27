#include "philo.h"

void	print_message(int phil_number, char *msg, t_table *table)
{
	long long	current_all;

	pthread_mutex_lock(&table->print_pause);
	if (gettimeofday(&table->time_el, NULL) != 0)
		printf("gettimeofdat in print_message fucked\n");
	current_all = table->time_el.tv_sec * 1000000 + table->time_el.tv_usec;
	printf("%lld %2d is %s\n", (current_all - table->time_start) / 1000,
			phil_number, msg);
	pthread_mutex_unlock(&table->print_pause);
}

void	sleep_philo(t_table *table, t_philosopher *philosopher)
{
	print_message(philosopher->number, "sleeping", table);
	my_usleep(table->time_to_sleep * 1000);
}

void	set_last_time_eat(t_philosopher *philosopher, t_table *table)
{
	struct timeval	time_el;

	if (gettimeofday(&time_el, NULL) != 0)
		printf("gettimeofdat in get_last_time_eat fucked\n");
	philosopher->last_eat = (time_el.tv_sec * 1000000 + time_el.tv_usec
		- table->time_start) / 1000;
}

void	eat(t_table *table, t_philosopher *philosopher)
{

	if (philosopher->number % 2)
	{
		
		pthread_mutex_lock(&(table->forks[philosopher->left_fork]));
		print_message(philosopher->number, "has taken a fork", table);
		pthread_mutex_lock(&(table->forks[philosopher->right_fork]));
		print_message(philosopher->number, "has taken a fork", table);
	}
	else 
	{
		pthread_mutex_lock(&(table->forks[philosopher->right_fork]));
		print_message(philosopher->number, "has taken a fork", table);
		pthread_mutex_lock(&(table->forks[philosopher->left_fork]));
		print_message(philosopher->number, "has taken a fork", table);
	}
	print_message(philosopher->number, "eating", table);
	my_usleep(table->time_to_eat * 1000);
	
	pthread_mutex_unlock(&(table->forks[philosopher->left_fork]));
	pthread_mutex_unlock(&(table->forks[philosopher->right_fork]));
	set_last_time_eat(philosopher, table);
	my_usleep(50);
}

void	*routin(void *arg)
{
	t_philosopher_args	*philosopher_args;
	t_philosopher		*philosopher;
	t_table				*table;

	philosopher_args = (t_philosopher_args*) arg;
	philosopher = (t_philosopher*) philosopher_args->philosopher;
	table = (t_table*) philosopher_args->table;

	// while (1)
	// 	{
			print_message(philosopher->number, "thinking", table);
			eat(table, philosopher);
			// sleep_philo(table, philosopher);
		// }
	return (NULL);
}

void	start(long long *params)
{
	pthread_t			*threads;
	t_philosopher		*philosophers;
	t_philosopher_args	*arguments;
	t_table				table;
	int					i;

	threads = malloc(params[0] * sizeof(pthread_t));
	table.forks = malloc(params[0] * sizeof(pthread_mutex_t));
	philosophers = malloc(params[0] * sizeof(t_philosopher));
	arguments = malloc(params[0] * sizeof(t_philosopher_args));
	if (!threads || !table.forks || !philosophers || !arguments)
		{
			printf("fuck up with malloc in start\n");
			return ;
		}
	init_philosophers(philosophers, params);
	i = 0;
	while (i < params[0])
	{
		arguments[i].philosopher = &philosophers[i];
		arguments[i].table = &table;
		i++;
	}
	init_table(&table, params);
	i = 0;
	while (i < params[0])
	{
		pthread_create(threads + i, NULL, &routin, arguments + i);
		i++;
	}
	i = 0;
	while (i < params[0])
	{
		printf("%d\n", i);
		pthread_join(threads[i], NULL);
		i++;
	}
	exit_routin(arguments, params, threads);

	return ;
}