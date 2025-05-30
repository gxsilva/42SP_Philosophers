/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:34:04 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/03 02:12:11 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int			init_value(char **argv, int argc, t_data *philo_s, int *cod);
static int	_alloc_data(t_data *philo_s);
static void	_init_forks(t_data *philo_s);
static void	_init_philo(t_data *philo_s);
static int	_init_data(char **argv, int argc, t_data *philo_s);

static int	_init_data(char **argv, int argc, t_data *philo_s)
{
	int		n_philo;

	n_philo = ft_atoi(argv[1]);
	if (n_philo <= 0 || n_philo > 200)
		return (-1);
	philo_s->philo_num = n_philo;
	philo_s->dead = 0;
	philo_s->finished = 0;
	philo_s->death_time = ft_atoi(argv[2]);
	philo_s->eat_time = ft_atoi(argv[3]);
	philo_s->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		philo_s->meals_nb = ft_atoi(argv[5]);
	else
		philo_s->meals_nb = -1;
	pthread_mutex_init(&philo_s->write, NULL);
	pthread_mutex_init(&philo_s->lock, NULL);
	return (1);
}

static int	_alloc_data(t_data *philo_s)
{
	philo_s->tid = (pthread_t *)malloc(sizeof(pthread_t) * philo_s->philo_num);
	if (!philo_s->tid)
		return (free_philo(philo_s), terminate_with_error(FAILED_MALLOC, -2));
	philo_s->forks = malloc(sizeof(pthread_mutex_t) * philo_s->philo_num);
	if (!philo_s->forks)
		return (free_philo(philo_s), terminate_with_error(FAILED_MALLOC, -2));
	philo_s->philos = malloc(sizeof(t_philo) * philo_s->philo_num);
	if (!philo_s->philos)
		return (free_philo(philo_s), terminate_with_error(FAILED_MALLOC, -2));
	return (1);
}

static void	_init_forks(t_data *philo_s)
{
	int		i;

	i = -1;
	while (++i < philo_s->philo_num)
		pthread_mutex_init(&philo_s->forks[i], NULL);
	philo_s->philos[0].l_fork = &philo_s->forks[0];
	philo_s->philos[0].r_fork = &philo_s->forks[philo_s->philo_num - 1];
	i = 0;
	while (++i < philo_s->philo_num)
	{
		philo_s->philos[i].l_fork = &philo_s->forks[i];
		philo_s->philos[i].r_fork = &philo_s->forks[i - 1];
	}
}

static void	_init_philo(t_data *philo_s)
{
	int		i;

	i = 0;
	while (i < philo_s->philo_num)
	{
		philo_s->philos[i].data = philo_s;
		philo_s->philos[i].id = i + 1;
		philo_s->philos[i].eat_cont = 0;
		philo_s->philos[i].status = 0;
		philo_s->philos[i].eating = 0;
		philo_s->philos[i].time_to_die = philo_s->death_time;
		pthread_mutex_init(&philo_s->philos[i].lock, NULL);
		i++;
	}
}

int	init_value(char **argv, int argc, t_data *philo_s, int *cod)
{
	if (_init_data(argv, argc, philo_s) < 0)
		return (*cod = 1, 0);
	if (_alloc_data(philo_s) < 0)
		return (*cod = 2, 0);
	_init_forks(philo_s);
	_init_philo(philo_s);
	return (1);
}
