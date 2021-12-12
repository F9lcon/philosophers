/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandr <aleksandr@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:13:40 by namina            #+#    #+#             */
/*   Updated: 2021/12/12 17:13:25 by aleksandr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct s_philosopher
{
	int				number;
	unsigned int	left_fork;
	unsigned int	right_fork;
	long long		last_eat_mcs;
	int				can_eat;
}					t_philosopher;

typedef struct s_fork_data
{
	pthread_mutex_t	mutex;
}					t_fork_data;

typedef struct s_table
{
	pthread_mutex_t	*forks;
	int				number_of_philo;
	int				times_to_eat;
	pthread_mutex_t	print_pause;
	struct timeval	time_el;
	int				all_alive;
	long long		time_start_mcs;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	pthread_t		*threads;
}					t_table;

typedef struct s_philosopher_args
{
	t_table			*table;
	t_philosopher	*philosopher;
}					t_philosopher_args;

void		detach_thread(t_philosopher_args *arguments);
void		*life_controller_thread(void *arg);
void		init_table(t_table *table, int params[]);
void		exit_routin(t_philosopher_args *args, int *params,
				pthread_t *threads);
void		my_usleep(int microseconds);
int			validation(int argc, char **argv, int **params);
void		serv_manager(int *params);
void		life_controller(t_philosopher_args *arguments);
void		set_last_time_eat(t_philosopher *philosopher, t_table *table);
long long	ft_atoi(const char *s);
int			ft_isdigit(int c);
void		print_message(int phil_number, char *msg, t_table *table,
				int isFinish);
void		create_args(int *params, t_philosopher_args **arguments);
char		*ft_itoa(int n);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
void		*routin(void *arg);
int			start_thread(int *params, t_philosopher_args *arguments,
				pthread_t *threads);
int			ft_strncmp(char const *s1, char const *s2, size_t n);
#endif