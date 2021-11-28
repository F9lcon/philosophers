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
	table->time_to_die = params[1];
	table->time_to_eat = params[2];
	table->time_to_sleep = params[3];
	pthread_mutex_init(&table->print_pause, NULL);
	if (gettimeofday(&table->time_el, NULL) != 0)
		printf("gettimeofday in init_table fucked\n");
	table->time_start_mcs = table->time_el.tv_sec * 1000000
				+ table->time_el.tv_usec;
	table->all_alive = 1;
	table->number_of_philo = params[0];

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

void detach_thread(t_philosopher_args* arguments)
{
	int	i;

	i = 0;
	printf("detach\n");
	while (i < arguments->table->number_of_philo)
	{
		pthread_join(arguments->table->threads[i], NULL);
		i++;
	}
}

void	waiter_start(t_philosopher_args* arguments)
{
	int				i;
	struct timeval	time_el;
	long long		current_time_mcs;
	t_philosopher	*philosopher;

	while (1)
	{
		i = 0;
		while (i < arguments->table->number_of_philo)
		{
			philosopher = (arguments + i)->philosopher;
			usleep(100);
			gettimeofday(&time_el, NULL);
			current_time_mcs = (time_el.tv_sec * 1000000 + time_el.tv_usec
				- arguments->table->time_start_mcs);
			if ((current_time_mcs - philosopher->last_eat_mcs)
					/ 1000 > (arguments + i)->table->time_to_die)
			{
				(arguments + i)->table->all_alive = 0;
				print_message(philosopher->number, "died", arguments->table);
				pthread_mutex_lock(&arguments->table->print_pause);
				detach_thread(arguments);
				return ;
			}
			i++;
		}
	}
}

t_philosopher_args	*create_args(long long *params)
{
	t_philosopher		*philosophers;
	t_table				*table;
	int					i;
	t_philosopher_args	*arguments;

	table = malloc(sizeof(t_table));
	table->forks = malloc(params[0] * sizeof(pthread_mutex_t));
	philosophers = malloc(params[0] * sizeof(t_philosopher));
	arguments = malloc(params[0] * sizeof(t_philosopher_args));
	if (!table || !table->forks || !philosophers || !arguments)
	{
		printf("fuck up with malloc in start\n");
		// add free func
		return (NULL);
	}
	init_philosophers(philosophers, params);
	i = 0;
	while (i < params[0])
	{
		(arguments + i)->philosopher = &philosophers[i];
		(arguments + i)->table = table;
		i++;
	}
	init_table(table, params);
	return (arguments);
}
