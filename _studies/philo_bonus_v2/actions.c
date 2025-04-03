/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:58:48 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/19 03:01:48 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	take_forks(t_philo *philo)
{
	if (get_state(philo->data))
		return (1);
	sem_wait(philo->data->s_forks);
	message(TAKE_FORK,TAKE_FORK, philo);
	sem_wait(philo->data->s_forks);
	message(TAKE_FORK, TAKE_FORK, philo);
	return (0);
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->data->s_forks);
	sem_post(philo->data->s_forks);
	message(SLEEP, SLEEP, philo);
	ft_usleep(philo->data->sleep_time, philo);
}

int	eat(t_philo *philo)
{
	if (get_state(philo->data))
		return (1);
	philo->time_to_die = get_time(philo->data) + philo->data->death_time;
	message(EATING,EATING, philo);
	philo->eat_cont++;
	ft_usleep(philo->data->eat_time, philo);
	return (0);
}

int	think_ph(t_philo *philo)
{
	if (get_state(philo->data))
		return (1);
	message(THINK, THINK, philo);
	ft_usleep(philo->data->sleep_time, philo);
	return (0);
}

int	sleep_ph(t_philo *philo)
{
	if (get_state(philo->data))
		return (1);
	message(SLEEP, SLEEP, philo);
	ft_usleep(philo->data->sleep_time, philo);
	return (0);
	
}