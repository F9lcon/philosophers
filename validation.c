#include "philo.h"

int validation(int argc, char **argv, long long **params)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (-1);
	*params = malloc(4 * sizeof(long long));
	argv++;
	while (*argv)
	{
		(*params)[i] = ft_atoi(*argv);
		i++;
		argv++;
	}
	// printf("%lld\n", params[0]);
	// if (params[0] <= 0)
	// 	{
	// 		printf("should be atleast one philo\n");
	// 		return (-1);
	// 	}
	return (0);
}