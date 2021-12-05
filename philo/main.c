/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namina <namina@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:10:01 by namina            #+#    #+#             */
/*   Updated: 2021/12/05 15:09:23 by namina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int	*params;

	params = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("For simulation need 4 or 5 arguments\n");
		return (-1);
	}
	if (validation(argc, argv + 1, &params) != 0)
		return (1);
	serv_manager(params);
	return (0);
}
