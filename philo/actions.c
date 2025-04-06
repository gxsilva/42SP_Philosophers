/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:51:03 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/06 15:55:48 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		message(TAKE_FORK, philo);
		pthread_mutex_lock(philo->l_fork);
		message(TAKE_FORK, philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		message(TAKE_FORK, philo);
		pthread_mutex_lock(philo->r_fork);
		message(TAKE_FORK, philo);
	}
}

static void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	message(SLEEP, philo);
	ft_usleep(philo->data->sleep_time, philo);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = get_time(philo->data) + philo->data->death_time;
	philo->eating = 1;
	message(EATING, philo);
	philo->eat_cont++;
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->data->eat_time, philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
