#include "philo_bonus.h"


void exec(int *pid, sem_t *forks)
{
	(void) forks;
	*pid = fork();
	if (*pid == 0)
	{
		sem_wait(forks);
		sleep(2);
		printf("hello from sem pause\n");
		sem_post(forks);
		exit(0);
	}


}

int main(void)
{
	int pids[5];
	int i = 0;
	sem_t	*forks;

	forks = sem_open("forks", O_CREAT, 777, 3);
	if (!forks)
	{
		printf("some shit with sem\n");
		return (1);
	}
	while (i < 5)
	{
		exec(pids + i, forks);
		i++;
	}
	i = 0;
	while(i < 5)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	return (0);
}