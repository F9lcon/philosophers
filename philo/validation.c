#include "philo.h"

int check_params(long long *params, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (params[i] <= 0)
		{
			printf("Argument #%d is incorrect\n", i + 1);
			free(params);
			return (-1);
		}
		i++;
	}
	return (0);
}

int validation(int argc, char **argv, long long **params)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		{
			printf("For simulation need 4 or 5 arguments\n");
			return (-1);
		}
	*params = malloc((argc - 1) * sizeof(long long));
	argv++;
	while (*argv)
	{
		(*params)[i] = ft_atoi(*argv);
		i++;
		argv++;
	}
	if (check_params(*params, argc) == -1)
		return (-1);
	if (argc == 5)
		(*params)[4] = -1;
	return (0);
}
