#include "philo.h"

void	print_message(int phil_number, char *msg, t_table *table)
{
	long long	current_time;

	pthread_mutex_lock(&table->print_pause);
	if (gettimeofday(&table->time_el, NULL) != 0)
		printf("gettimeofdat in print_message fucked\n");
	current_time = table->time_el.tv_sec * 1000000 + table->time_el.tv_usec;
	printf("%lld %d %s\n", (current_time - table->time_start_mcs) / 1000,
			phil_number, msg);
	pthread_mutex_unlock(&table->print_pause);
}

void	sleep_philo(t_table *table, t_philosopher *philosopher)
{
	print_message(philosopher->number, "is sleeping", table);
	my_usleep(table->time_to_sleep * 1000);
}

void	set_last_time_eat(t_philosopher *philosopher, t_table *table)
{
	struct timeval	time_el;

	if (gettimeofday(&time_el, NULL) != 0)
		printf("gettimeofdat in get_last_time_eat fucked\n");
	philosopher->last_eat_mcs = (time_el.tv_sec * 1000000 + time_el.tv_usec
		- table->time_start_mcs);
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
	set_last_time_eat(philosopher, table);
	print_message(philosopher->number, "is eating", table);
	my_usleep(table->time_to_eat * 1000);
	if (philosopher->number % 2)
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

	philosopher_args = (t_philosopher_args*) arg;
	philosopher = (t_philosopher*) philosopher_args->philosopher;
	table = (t_table *) philosopher_args->table;
	set_last_time_eat(philosopher, table);
	while (1)
	{
		print_message(philosopher->number, "is thinking", table);
		eat(table, philosopher);
		// my_usleep(1000);
		sleep_philo(table, philosopher);
	}
	return (NULL);
}

void *waiter_routing(void *arg)
{
	t_philosopher_args	*arguments;

	arguments = (t_philosopher_args *) arg;
	waiter_start(arguments);
	return (NULL);
}

void	serv_manager(long long *params)
{
	pthread_t			*threads;
	pthread_t			waiter_thread;
	t_philosopher_args	*arguments;
	int					i;

	threads = malloc(params[0] * sizeof(pthread_t));
	if (!threads)
		return ;
	arguments = create_args(params);
	arguments->table->threads = threads;
	i = 0;
	while (i < params[0])
	{
		pthread_create(threads + i, NULL, &routin, arguments + i);
		i++;
	}
	pthread_create(&waiter_thread, NULL, &waiter_routing, arguments);
	// waiter_start(arguments);
	i = 0;
	pthread_join(waiter_thread, NULL);
	while (i < params[0])
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	// exit_routin(arguments, params, threads);

	return ;
}