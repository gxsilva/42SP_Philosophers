/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:51:03 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/06 15:07:38 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"


static void take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	message(TAKE_FORK, philo);
	pthread_mutex_lock(philo->l_fork);
	message(TAKE_FORK, philo);
}

void eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_to_die = get_time(philo->data) + philo->data->death_time; //reset time to die
	message(EATING, philo);
	philo->eat_cont++;
	
}

/*
	philo -> take fork Right -> take fork Left -> eat_time -> release right fork
	-> release left fork -> sleep time
*/