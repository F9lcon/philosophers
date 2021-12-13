/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandr <aleksandr@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:14:18 by namina            #+#    #+#             */
/*   Updated: 2021/12/13 20:14:32 by aleksandr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	print_message(int phil_number, char *msg, t_table *table)
{
	char		*str;
	char		*number_str;
	long long	current_time;

	number_str = ft_itoa(phil_number);
	gettimeofday(&table->time_el, NULL);
	current_time = table->time_el.tv_sec * 1000000 + table->time_el.tv_usec;
	str = ft_itoa((current_time - table->time_start_mcs) / 1000);
	str = ft_strjoin(str, " ");
	str = ft_strjoin(str, number_str);
	str = ft_strjoin(str, " ");
	str = ft_strjoin(str, msg);
	str = ft_strjoin(str, "\n");
	sem_wait(table->print_pause);
	write(1, str, ft_strlen(str));
	if (ft_strncmp(msg, "died", 4))
		sem_post(table->print_pause);
	if (str)
		free(str);
	if (number_str)
		free(number_str);
}

void	set_last_time_eat(t_philosopher *philosopher, t_table *table)
{
	struct timeval	time_el;

	gettimeofday(&time_el, NULL);
	philosopher->last_eat_mcs = (time_el.tv_sec * 1000000 + time_el.tv_usec
			- table->time_start_mcs);
}

void	start_wait(int *pids, t_philosopher_args *arguments, int *params)
{
	int	exit_status;
	int	i;

	i = 0;
	waitpid(-1, &exit_status, 0);
	if (WEXITSTATUS(exit_status) == 42)
		kill_all_process(pids, arguments->table);
	else
	{
		while (i < params[0])
		{
			waitpid(pids[i], &exit_status, 0);
			i++;
		}
		printf("Everyone finish with meal\n");
	}
}

void	exit_routin(t_philosopher_args *args, int *params, int *pids)
{
	t_table			*table;
	t_philosopher	*philosophers;

	if (params)
		free(params);
	if (pids)
		free(pids);
	if (!args)
		return ;
	table = args->table;
	if (table)
	{
		sem_close(table->print_pause);
		unlink(PRINT_PAUSE);
		sem_close(table->forks);
		unlink(FORKS);
		free(table);
	}
	philosophers = args->philosopher;
	if (philosophers)
		free(philosophers);
	free(args);
}
