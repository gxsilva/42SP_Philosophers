/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:58:48 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/14 16:34:25 by lsilva-x         ###   ########.fr       */
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
	message(DROP_FORK, philo);
	ft_usleep(philo->data->sleep_time, philo);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	sem_wait(philo->data->ph_lock);
	philo->eating = 1;
	philo->time_to_die = get_time(philo->data) + philo->data->death_time;
	message(EATING, philo);
	philo->eat_cont++;
	ft_usleep(philo->data->eat_time, philo);
	philo->eating = 0;
	sem_post(philo->data->ph_lock);
	drop_forks(philo);
}
