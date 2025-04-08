/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:58:48 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/08 18:47:34 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	look_up(t_philo *philo)
{
	if (get_time(philo->data) >= philo->time_to_die + 1)
	{
		message(DIED, philo);
		sem_close(philo->data->write);
		sem_close(philo->data->forks);
		free_philo(philo->data);
		exit (EXIT_FAILURE);
	}
}

static void	wait_fork(t_philo *philo)
{
	while (*(int16_t *)philo->data->forks < 2)
		look_up(philo);
}

static void	take_forks(t_philo *philo)
{
	wait_fork(philo);
	sem_wait(philo->data->forks);
	message(TAKE_FORK, philo);
	sem_wait(philo->data->forks);
	message(TAKE_FORK, philo);
}

static void	drop_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	message(SLEEP, philo);
	ft_usleep(philo->data->sleep_time, philo);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	philo->time_to_die = get_time(philo->data) + philo->data->death_time;
	look_up(philo);
	message(EATING, philo);
	philo->eat_cont--;
	look_up(philo);
	ft_usleep(philo->data->eat_time, philo);
	drop_forks(philo);
	look_up(philo);
}
