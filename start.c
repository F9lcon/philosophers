#include "philo.h"

void	eat(t_table *table, t_philosopher *philosopher)
{
	my_usleep(100);
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
	set_last_time_eat(philosopher, table);
	print_message(philosopher->number, "is eating", table);
	my_usleep(table->time_to_eat * 1000);
	if (!philosopher->number % 2)
	{
		pthread_mutex_unlock(&(table->forks[philosopher->left_fork]));
		pthread_mutex_unlock(&(table->forks[philosopher->right_fork]));
	}
	else
	{
		pthread_mutex_unlock(&(table->forks[philosopher->right_fork]));
		pthread_mutex_unlock(&(table->forks[philosopher->left_fork]));
	}
}

void	*routin(void *arg)
{
	t_philosopher_args	*philosopher_args;
	t_philosopher		*philosopher;
	t_table				*table;
	int					i;

	i = 0;
	philosopher_args = (t_philosopher_args*) arg;
	philosopher = (t_philosopher*) philosopher_args->philosopher;
	table = (t_table *) philosopher_args->table;
	set_last_time_eat(philosopher, table);
	while (1)
	{
		if (table->times_to_eat != -1)
		{
			if (i >= table->times_to_eat)
				break ;
		}
		print_message(philosopher->number, "is thinking", table);
		eat(table, philosopher);
		print_message(philosopher->number, "is sleeping", table);
		my_usleep(table->time_to_sleep * 1000);
		i++;
	}
	philosopher->can_eat = 0;
	return (NULL);
}

void	serv_manager(long long *params)
{
	pthread_t			*threads;
	pthread_t			waiter_thread;
	t_philosopher_args	*arguments;
	int					i;

	arguments = create_args(params);
	threads = malloc(params[0] * sizeof(pthread_t));
	if (!threads)
		return ;
	arguments->table->threads = threads;
	i = 0;
	while (i < params[0])
	{
		pthread_create(threads + i, NULL, &routin, arguments + i);
		i++;
	}
	pthread_create(&waiter_thread, NULL, &waiter_routing, arguments);
	i = 0;
	pthread_join(waiter_thread, NULL);
	while (i < params[0])
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	exit_routin(arguments, params, threads);

	return ;
}