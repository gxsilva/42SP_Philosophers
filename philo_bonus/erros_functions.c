/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erros_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:04:23 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/17 20:46:05 by lsilva-x         ###   ########.fr       */
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
	if (philo_s->philos != NULL)
	{
		free(philo_s->philos);
		philo_s->philos = NULL;
	}
	if (philo_s->pid != NULL)
	{
		free(philo_s->pid);
		philo_s->pid = NULL;
	}
	free(philo_s);
}

void	free_philo(t_data *philo_s)
{
	int		i;

	if (philo_s == NULL)
		return ;
	sem_destroy(philo_s->write);
	if (philo_s->forks != NULL)
	{
		i = -1;
		while (++i < philo_s->philo_num)
			sem_destroy(&philo_s->forks[i]);
		free(philo_s->forks);
		philo_s->forks = NULL;
	}
	free_node(philo_s);
}

void	clear_data(t_data *philo_s)
{
	if (philo_s->pid)
		free(philo_s->pid);
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
		sem_destroy(&philo_s->forks[i]);
	sem_destroy(philo_s->write);
	sem_destroy(philo_s->lock);
	clear_data(philo_s);
}
