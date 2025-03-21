/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:58:48 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/19 01:32:33 by lsilva-x         ###   ########.fr       */
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
	if (get_state(philo->data) != 0)
		return ;
	take_forks(philo);
	sem_wait(philo->data->ph_lock);
	philo->time_to_die = get_time(philo->data) + philo->data->death_time;
	message(EATING, philo);
	philo->eat_cont++;
	sem_post(philo->data->ph_lock);
	ft_usleep(philo->data->eat_time, philo);
	drop_forks(philo);
}
