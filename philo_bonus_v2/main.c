/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:23:38 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/18 18:27:45 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	clean_pcr(t_data *philo)
{
	sem_close(philo->s_forks);
	// sem_close(philo->s_print_died);
	sem_close(philo->s_state_end);
	sem_close(philo->s_write);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_STATE_END);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_PRINT_DIED);
}

int main(int argc, char **argv)
{
	t_data	philo_s;
	
	if (argc < 5 || argc > 6)
		terminate_with_error(INPUT_NUMBER, -1);
	input_checker(argc, argv);
	init_value(argv, argc, &philo_s);
	if(start_philo(&philo_s))
	{
		clean_pcr(&philo_s);
		return (-1);
	}
	clean_pcr(&philo_s);
	return (0);
}

int	kill_process(t_data *philo_s)
{
	printf("Kill process\n");
	int	i;

	i = 0;
	while (i < philo_s->philo_num)
	{
		if (philo_s->pid[i] > 0)
			kill(philo_s->pid[i], SIGTERM);
		i++;
	}
	return (0);
}
