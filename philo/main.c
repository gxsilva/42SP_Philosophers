/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:26:08 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/02/27 20:15:24 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

void	input_checker(char **argv, t_data	*philo_s)
{
	int		n_philo;

	n_philo = ft_atoi(argv[1]);
	if (n_philo <= 0 || n_philo > 200)
		printf("[Error]: Philosopher count out of range (1-200)\n");
	philo_s->philo_num = n_philo;
	
}

int	main(int argc, char **argv)
{
	t_data	*philo_s;
	if (argc < 5 || argc > 6)
	{
		printf("[Error]: Number of invalid arguments, min 4 | max 5\n");
		return (1);
	}
	philo_s = (t_data *)malloc(sizeof(t_data));
	if (!philo_s)
	{
		printf("[Error]: Memory Allocation error\n");
		return (1);
	}
	input_checker(argv, philo_s);
}
