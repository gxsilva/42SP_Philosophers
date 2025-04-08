/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:18:25 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/08 18:55:36 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	close_semaphore(t_data *philo_s)
{
	if (philo_s->forks)
		sem_close(philo_s->forks);
	if (philo_s->write)
		sem_close(philo_s->write);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_LOCK);
	sem_unlink(SEM_WRITE);
}
