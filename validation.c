#include "philo.h"

int validation(int argc, char **argv, long long **params)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (-1);
	*params = malloc((argc - 1) * sizeof(long long));
	argv++;
	while (*argv)
	{
		(*params)[i] = ft_atoi(*argv);
		i++;
		argv++;
	}
	if (argc == 5)
		(*params)[4] = -1;
	return (0);
}