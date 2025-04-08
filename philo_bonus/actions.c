/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:58:48 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/08 02:35:25 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	take_forks(t_philo *philo)
{
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
	if (!is_alive(philo->data, 0))
	{
		take_forks(philo);
		sem_wait(philo->data->lock);
		philo->time_to_die = get_time(philo->data) + philo->data->death_time;
		sem_post(philo->data->lock);
		message(EATING, philo);
		sem_wait(philo->data->lock);
		philo->eat_cont--;
		sem_post(philo->data->lock);
		ft_usleep(philo->data->eat_time, philo);
		drop_forks(philo);
	}
}
