#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>



typedef struct	s_list
{
	struct s_list	*next;
	void			*content;
}					t_list;

typedef struct	s_philosopher
{
	int			number;
	unsigned	left_fork;
	unsigned	right_fork;
}				t_philosopher;

typedef struct s_fork_data
{
	pthread_mutex_t	mutex;
	int				number;
}					t_fork_data;

typedef struct s_entry
{
	unsigned		left_fork;
	unsigned		right_fork;
	pthread_mutex_t	point;
}					t_entry;

typedef struct	s_table
{
	pthread_mutex_t	*forks;
	t_entry			*entry_arr;
	pthread_mutex_t	entry_point;
	struct timeval	time_el;
	long long 		time_start;
	long long		time_to_eat;
	long long		time_to_sleep;
}					t_table;



typedef struct	s_philosopher_args
{
	t_table			*table;
	t_philosopher	*philosopher;
}					t_philosopher_args;

void		init_table(t_table *table, long long params[],
			t_entry *entry_arr);
void		destroy_mutex(t_table *table, long long params[],
			t_entry *entry_arr);
void		my_usleep(long long microseconds);
int			validation(int argc, char **argv, long long *params);
void		start(long long *params);
long long	ft_atoi(const char *s);
int			ft_isdigit(int c);

// void		init_philosopher(t_philosopher *philosopher, int number,
// 		unsigned left_fork, unsigned right_fork);
void	init_philosophers(t_philosopher *philosophers,
			long long *params, t_entry *entry_arr);

/* list funcs*/
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);