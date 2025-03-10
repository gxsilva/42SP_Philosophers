/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erros_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:04:23 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/10 15:42:59 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void		terminate_with_error(char *str, int exit_cod);
void		free_philo(t_data *philo_s);
void		clear_data(t_data *philo_s);
void		ft_exit(t_data *philo_s);
static void	free_node(t_data *philo_s);

void	terminate_with_error(char *str, int exit_cod)
{
	printf("[Error]: %s\n", str);
	exit (exit_cod);
}

static void	free_node(t_data *philo_s)
{
	int		i;

	if (philo_s->philos != NULL)
	{
		i = -1;
		while (++i < philo_s->philo_num)
			pthread_mutex_destroy(&philo_s->philos[i].lock);
		free(philo_s->philos);
		philo_s->philos = NULL;
	}
	if (philo_s->tid != NULL)
	{
		free(philo_s->tid);
		philo_s->tid = NULL;
	}
	free(philo_s);
}

void	free_philo(t_data *philo_s)
{
	int		i;

	if (philo_s == NULL)
		return ;
	pthread_mutex_destroy(&philo_s->write);
	if (philo_s->forks != NULL)
	{
		i = -1;
		while (++i < philo_s->philo_num)
			pthread_mutex_destroy(&philo_s->forks[i]);
		free(philo_s->forks);
		philo_s->forks = NULL;
	}
	free_node(philo_s);
}

void	clear_data(t_data *philo_s)
{
	if (philo_s->tid)
		free(philo_s->tid);
	if (philo_s->forks)
		free(philo_s->forks);
	if (philo_s->philos)
		free(philo_s->philos);
}

void	ft_exit(t_data *philo_s)
{
	int	i;

	i = -1;
	while (++i < philo_s->philo_num)
	{
		pthread_mutex_destroy(&philo_s->forks[i]);
		pthread_mutex_destroy(&philo_s->philos[i].lock);
	}
	pthread_mutex_destroy(&philo_s->write);
	pthread_mutex_destroy(&philo_s->lock);
	clear_data(philo_s);
}
