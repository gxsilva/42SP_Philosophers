/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:34:04 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/08 02:52:32 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void		init_value(char **argv, int argc, t_data *philo_s);
static void	alloc_data(t_data *philo_s);
static void	init_forks(t_data *ph);
static void	init_philo(t_data *philo_s);

static void	init_data(char **argv, int argc, t_data *philo_s)
{
	int		n_philo;

	n_philo = ft_atoi(argv[1]);
	if (n_philo <= 0 || n_philo > 200)
		terminate_with_error(PHI_OUT_RANGE, -1);
	philo_s->philo_num = n_philo;
	philo_s->dead = 0;
	philo_s->death_time = ft_atoi(argv[2]);
	philo_s->eat_time = ft_atoi(argv[3]);
	philo_s->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		philo_s->meals_nb = ft_atoi(argv[5]);
	else
		philo_s->meals_nb = -1;
}

static void	alloc_data(t_data *philo_s)
{
	philo_s->pid = (pid_t *)malloc(sizeof(pid_t) * philo_s->philo_num);
	if (!philo_s->pid)
		terminate_with_error(FAILED_MALLOC, -2);
	philo_s->philos = malloc(sizeof(t_philo) * philo_s->philo_num);
	if (!philo_s->philos)
	{
		free(philo_s->pid);
		terminate_with_error(FAILED_MALLOC, -2);
	}
}

static void	init_forks(t_data *ph)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_LOCK);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_PH_LOCK);
	ph->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0644, ph->philo_num);
	ph->lock = sem_open(SEM_LOCK, O_CREAT | O_EXCL, 0644, 1);
	ph->write = sem_open(SEM_WRITE, O_CREAT | O_EXCL, 0644, 1);
	ph->ph_lock = sem_open(SEM_PH_LOCK, O_CREAT | O_EXCL, 0644, 1);
}

static void	init_philo(t_data *philo_s)
{
	int		i;

	i = 0;
	while (i < philo_s->philo_num)
	{
		philo_s->philos[i].data = philo_s;
		philo_s->philos[i].id = i + 1;
		philo_s->philos[i].eat_cont = philo_s->meals_nb;
		philo_s->philos[i].status = 0;
		philo_s->philos[i].eating = 0;
		philo_s->philos[i].time_to_die = philo_s->death_time;
		i++;
	}
}

void	init_value(char **argv, int argc, t_data *philo_s)
{
	init_data(argv, argc, philo_s);
	alloc_data(philo_s);
	init_forks(philo_s);
	init_philo(philo_s);
}
