/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleksandr <aleksandr@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 21:10:01 by namina            #+#    #+#             */
/*   Updated: 2021/12/15 18:12:27 by aleksandr        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	int	*params;

	params = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("For simulation need 4 or 5 arguments\n");
		return (1);
	}
	if (validation(argc, argv + 1, &params) != 0)
		return (1);
	serv_manager(params);
	return (0);
}


// add to man part 
// free philosophers array

