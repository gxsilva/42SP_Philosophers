/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:58:58 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/04 12:54:28 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*monitor(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished >= philo->data->philo_num)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

void	*supervisor(void *args)
{
	t_philo		*ph;

	ph = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&ph->data->lock);
		if (ph->data->dead != 0)
		{
			pthread_mutex_unlock(&ph->data->lock);
			break ;
		}
		if (get_time(ph->data) >= (ph->time_to_die + 1) && ph->eating == 0)
		{
			pthread_mutex_unlock(&ph->data->lock);
			message(DIED, ph);
			return (NULL);
		}
		else if (ph->eat_cont == ph->data->meals_nb)
		{
			ph->data->finished++;
			ph->eat_cont++;
		}
		pthread_mutex_unlock(&ph->data->lock);
		usleep(100);
	}
	return (NULL);
}

void	*routine(void *args)
{
	t_philo		*philo;
	t_data		*p_data;

	philo = (t_philo *)args;
	philo->time_to_die = philo->data->death_time + get_time(philo->data);
	p_data = philo->data;
	if (pthread_create(&philo->t1, NULL, supervisor, (void *)philo))
	{
		free_philo(p_data);
		terminate_with_error(TH_CREATE, -4);
		return (NULL);
	}
	while (philo->data->dead == 0)
	{
		eat(philo);
		message(THINK, philo);
	}
	if (pthread_join(philo->t1, NULL))
		return (NULL);
	return (NULL);
}
