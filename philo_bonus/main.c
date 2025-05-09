/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:42:05 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/09 15:04:51 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	_single_philo(t_data *philo_s);
void		kill_process(t_data *philo_s);

int	main(int argc, char **argv)
{
	t_data	philo_s;
	pid_t	tmp_pid;

	if (argc < 5 || argc > 6)
		terminate_with_error(INPUT_NUMBER, -1);
	input_checker(argv);
	init_value(argv, argc, &philo_s);
	if (philo_s.philo_num == 1)
	{
		tmp_pid = _single_philo(&philo_s);
		waitpid(-1, &tmp_pid, 0);
		close_semaphore(&philo_s);
		free_philo(&philo_s);
	}
	else
	{
		start_philo(&philo_s);
		close_semaphore(&philo_s);
		free_philo(&philo_s);
	}
	return (0);
}

static int	_single_philo(t_data *philo_s)
{
	pid_t	pid;
	t_philo	*ph;

	ph = &philo_s->philos[0];
	pid = fork();
	if (pid == -1)
		terminate_with_error(FK_CREATE, -5);
	if (pid == 0)
	{
		philo_s->start_time = get_time(philo_s);
		ph->time_to_die = philo_s->death_time - get_time(philo_s);
		sem_wait(ph->data->forks);
		message(TAKE_FORK, ph);
		ft_usleep(ph->data->death_time, ph);
		message(DIED, ph);
		sem_close(philo_s->write);
		sem_close(philo_s->forks);
		free_philo(philo_s);
		exit(-1);
	}
	return (pid);
}

void	kill_process(t_data *philo_s)
{
	int	i;

	i = -1;
	while (++i < philo_s->philo_num)
		kill(philo_s->pid[i], SIGKILL);
}
