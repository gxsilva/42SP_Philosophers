/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:58:58 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/09 20:40:50 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void *monitor(void *args)
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
//responsible to verify and update informations
void *supervisor(void *args)
{
	t_philo		*philo;

	philo	= (t_philo *)args;
	//start the supervisor
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time(philo->data) >= philo->time_to_die && philo->eating == 0)
			message(DIED, philo);
		if (philo->eat_cont == philo->data->meals_nb)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->eat_cont++; // ??? wtf is this
			pthread_mutex_unlock(&philo->data->lock);
		} 
	}
	pthread_mutex_unlock(&philo->lock);
	return (NULL);
}

void	*routine(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	philo->time_to_die = philo->data->death_time + get_time(philo->data);
	if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo))
	{
		free_philo(philo->data);
		terminate_with_error(TH_CREATE, -4);
	}
	while (1)
	{
		eat(philo);
		message(THINK, philo);
	}
	if (pthread_join(philo->t1, NULL))
		return (NULL);
	return (NULL);
}
