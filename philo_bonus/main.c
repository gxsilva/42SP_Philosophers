/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:42:05 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/17 19:13:19 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	kill_process(t_data *philo_s);

int main(int argc, char **argv)
{
	t_data	philo_s;
	
	if (argc < 5 || argc > 6)
		terminate_with_error(INPUT_NUMBER, -1);
	input_checker(argc, argv);
	init_value(argv, argc, &philo_s);
	start_philo(&philo_s);
	return (0);
}
void	kill_process(t_data *philo_s)
{
	printf("KILLLLLLLLLLL");
	int	i;

	i = 0;
	while (i < philo_s->philo_num)
	{
		if (philo_s->pid[i] > 0)
			kill(philo_s->pid[i], SIGTERM);
		i++;
	}
}
