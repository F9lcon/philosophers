#include "philo.h"

void	init_table(t_table *table, long long params[],
			t_entry *entry_arr)
{
	int	i;

	i = 0;

	while (i < params[0])
	{
		pthread_mutex_init(table->forks + i, NULL);
		pthread_mutex_init(&((entry_arr + i)->point), NULL);
		i++;
	}
	if (gettimeofday(&table->time_el, NULL) != 0)
		printf("gettimeofday in init_table fucked\n");
	table->time_start = table->time_el.tv_sec * 1000000
				+ table->time_el.tv_usec;
	table->time_to_eat = params[2];
	table->time_to_sleep = params[3];

	pthread_mutex_init(&table->entry_point, NULL);

}

void destroy_mutex(t_table *table, long long params[],
			t_entry *entry_arr)
{
	int	i;

	i = 0;
	while (i < params[0])
	{
		pthread_mutex_destroy(table->forks + i); 
		pthread_mutex_destroy((&((entry_arr + i)->point)));
		i++;
	}

	pthread_mutex_destroy(&table->entry_point);
	// free(table->forks);
}

// void init_philosopher(t_philosopher *philosopher, int number,
// 		unsigned left_fork, unsigned right_fork)

void	init_philosophers(t_philosopher *philosophers,
		long long *params, t_entry *entry_arr)
{
	int	i;
	int	entry_i;

	i = 0;
	entry_i = 0;
	while (i < params[0])
	{
		(&philosophers[i])->number = i + 1;
		(&philosophers[i])->left_fork = i;
		(&entry_arr[entry_i])->left_fork = i;
		if (i + 1 == params[0])
		{
			(&philosophers[i])->right_fork = 0;
			(&entry_arr[entry_i])->right_fork = 0;
		}
		else
		{
			(&philosophers[i])->right_fork = i + 1;
			(&entry_arr[entry_i])->right_fork = i + 1;
		}

/* just print*/
		// printf("philo %d left %d right %d\n", (&philosophers[i])->number,
		// (&philosophers[i])->left_fork,
		// (&philosophers[i])->right_fork);
		// printf("entry left %d right %d\n",
		// (&entry_arr[entry_i])->left_fork,
		// (&entry_arr[entry_i])->right_fork);

/* end of printing*/
		i++;
		entry_i++;
	}


	// philosopher->number = number;
	// philosopher->left_fork = left_fork;
	// philosopher->right_fork = right_fork;
}