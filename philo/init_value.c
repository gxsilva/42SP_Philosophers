/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:34:04 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/02/28 17:29:27 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	init_value(char **argv, int argc, t_data *philo_s);

void	init_data(char **argv, int argc, t_data *philo_s)
{
	int		n_philo;

	n_philo = ft_atoi(argv[1]);
	if (n_philo <= 0 || n_philo > 200)
	{
		free(philo_s);
		terminate_with_error(PHI_OUT_RANGE, -1);
	}
	philo_s->philo_num = n_philo;
	philo_s->death_time = ft_atoi(argv[2]);
	philo_s->eat_time = ft_atoi(argv[3]);
	philo_s->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		philo_s->meals_nb = ft_atoi(argv[5]);
	else
		philo_s->meals_nb = -1;
	pthread_mutex_init(&philo_s->write, NULL); // Prevent multiple thread to write in STDOUT
	pthread_mutex_init(&philo_s->lock, NULL); //protec shared variable of the race condition
}

void	alloc_data(t_data *philo_s)
{
	philo_s->tid = (pthread_t *)malloc(sizeof(pthread_t) * philo_s->philo_num);
	if (!philo_s->tid)
	{
		free_philo(philo_s);
		terminate_with_error(FAILED_MALLOC, -2);
	}
	philo_s->forks = malloc(sizeof(pthread_mutex_t *) *  philo_s->philo_num);
	if (!philo_s->forks)
	{
		free_philo(philo_s);
		terminate_with_error(FAILED_MALLOC, -2);
	}
	philo_s->philos = malloc(sizeof(t_philo) * philo_s->philo_num);
	if (!philo_s->philos)
	{
		free_philo(philo_s);
		terminate_with_error(FAILED_MALLOC, -2);
	}
}

void	init_value(char **argv, int argc, t_data *philo_s)
{
	init_data(argv, argc, philo_s);
	alloc_data(philo_s);
}