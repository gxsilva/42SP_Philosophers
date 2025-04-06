/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:58:58 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/06 17:59:58 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_alive(t_data *data, int mod)
{
	int	dead_status;

	pthread_mutex_lock(&data->lock);
	if (mod == 0)
	{
		dead_status = data->dead;
		pthread_mutex_unlock(&data->lock);
		return (dead_status);
	}
	else
	{
		data->dead = 1;
		pthread_mutex_unlock(&data->lock);
		return (-1);
	}
}

void	*monitor(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	while (!is_alive(philo->data, 0))
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finished >= philo->data->philo_num)
		{
			pthread_mutex_unlock(&philo->data->lock);
			is_alive(philo->data, 1);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
		ft_usleep(500, philo);
	}
	return (NULL);
}

void	*supervisor(void *args)
{
	t_philo		*ph;

	ph = (t_philo *)args;
	while (!is_alive(ph->data, 0))
	{
		pthread_mutex_lock(&ph->lock);
		if (get_time(ph->data) >= (ph->time_to_die + 1) && ph->eating == 0)
		{
			pthread_mutex_unlock(&ph->lock);
			message(DIED, ph);
			continue ;
		}
		else if (ph->eat_cont == ph->data->meals_nb)
		{
			pthread_mutex_unlock(&ph->lock);
			pthread_mutex_lock(&ph->data->lock);
			ph->data->finished++;
			ph->eat_cont++;
			pthread_mutex_unlock(&ph->data->lock);
			continue ;
		}
		pthread_mutex_unlock(&ph->lock);
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
	while (!is_alive(philo->data, 0))
	{
		eat(philo);
		message(THINK, philo);
	}
	if (pthread_join(philo->t1, NULL))
		return (NULL);
	return (NULL);
}
