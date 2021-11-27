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

int	find_entry(t_philosopher *philosopher,
			t_entry entry_arr[], pthread_mutex_t *entry_point)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (entry_arr[i].left_fork == philosopher->left_fork
		|| entry_arr[i].right_fork == philosopher->right_fork
		|| entry_arr[i].left_fork == philosopher->right_fork
		|| entry_arr[i].right_fork == philosopher->left_fork)
		{
			*entry_point = entry_arr->point;
			return (0);
		}
		i++;
	}
	return (-1);
}

void	eat(t_table *table, t_philosopher *philosopher,
			pthread_mutex_t	entry_point)
{
// 	if (pthread_mutex_lock(&entry_point) != 0)
// 	{
// 		printf("lock entry fail\n");
// 		return ;
// 	}
	(void) entry_point;
	pthread_mutex_lock(&table->entry_point);
	if (pthread_mutex_lock(&(table->forks[philosopher->left_fork])) != 0)
	{
		printf("lock left fork fail\n");
		return ;
	}

	print_message(philosopher->number, "eating", table);
	my_usleep(table->time_to_eat * 1000);
	
	if (pthread_mutex_lock(&(table->forks[philosopher->right_fork])) != 0)
	{
		printf("lock right fork fail\n");
		return ;
	}
	pthread_mutex_unlock(&table->entry_point);


	pthread_mutex_unlock(&(table->forks[philosopher->left_fork]));
	pthread_mutex_unlock(&(table->forks[philosopher->right_fork]));
	// pthread_mutex_unlock(&entry_point);


	my_usleep(100);
}

void	*routin(void *arg)
{
	t_philosopher_args	*philosopher_args;
	t_philosopher		*philosopher;
	t_table				*table;
	pthread_mutex_t		entry_point;

	

	philosopher_args = (t_philosopher_args*) arg;
	philosopher = (t_philosopher*) philosopher_args->philosopher;
	table = (t_table*) philosopher_args->table;
	if (find_entry(philosopher, table->entry_arr, &entry_point) == -1)
		{
			printf("we fucked in find entry\n");
			return (NULL);
		}

	while (1)
		{
			eat(table, philosopher, entry_point);
			// sleep_philo(table, philosopher);
			// print_message(philosopher->number, "thinking", table);
		}
	return (NULL);
}

void	start(long long *params)
{
	pthread_t			threads[params[0]];
	pthread_mutex_t		fork_arr[params[0]];
	t_philosopher		philosophers[params[0]];
	t_philosopher_args	arguments[params[0]];
	t_entry				entry_arr[params[0]];
	t_table				table; // arr of mutex
	int					i;


	// set arr of philosophers
	table.entry_arr = entry_arr;
	table.forks = malloc(params[0] * sizeof(pthread_mutex_t));
	table.forks = fork_arr;
	init_philosophers(philosophers, params, entry_arr);
	// set arr of mutex
	init_table(&table, params, entry_arr);
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

	destroy_mutex(&table, params, entry_arr);

	return ;
}