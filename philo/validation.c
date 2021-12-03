#include "philo.h"

int check_params(int *params, int argc)
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

int validation(int argc, char **argv, int **params)
{
	int			i;
	long long	temp_value;

	i = 0;
	if (argc < 5 || argc > 6)
		{
			printf("For simulation need 4 or 5 arguments\n");
			return (-1);
		}
	*params = malloc((argc - 1) * sizeof(int));
	while (*argv)
	{
		temp_value = ft_atoi(*argv);
		if (temp_value > 2147483647)
			(*params)[i] = 2147483647;
		else
			(*params)[i] = temp_value;
		printf("param %d\n", (*params)[i]);
		i++;
		argv++;
	}
	if (check_params(*params, argc) == -1)
		return (-1);
	if (argc == 5)
		(*params)[4] = -1;
	return (0);
}
