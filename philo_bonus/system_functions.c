/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:14:11 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/07 01:27:27 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*supervisor(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	while (!is_alive(philo->data, 0))
	{
		sem_wait(philo->data->lock);
		if (get_time(philo->data) >= (philo->time_to_die + 1))
		{
			sem_post(philo->data->lock);
			message(DIED, philo);
			continue;
		}
		sem_post(philo->data->lock);
		usleep(100);
	}
	return (NULL);
}


int	monitor(t_data *philo_s)
{
	int	i;
	int	finished;
	int	status;

	i = 0;
	finished = 0;
	while (1)
	{
		if (i < philo_s->philo_num)
		{
			if (waitpid(philo_s->philos[i].pid, &status, WNOHANG) > 0)
			{
				if (WEXITSTATUS(status) == 1)
				{
					kill_process(philo_s);
					break;
				}
				if (WEXITSTATUS(status) == 0)
					finished++;
			}
			i++;
		}
		if (philo_s->finished == finished)
			return (kill_process(philo_s), 1);
		i = 0;
		usleep(10);
	}
	return (0);
}

int	take_process(t_data *philo_s)
{
	int	i;
	int	status;

	i = 0;
	while (1)
	{
		waitpid(philo_s->philos[i].pid, &status, WNOHANG);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				kill_process(philo_s);
				break ;
			}
		}
		i++;
		if (i >= philo_s->philo_num)
			i = 0;
		usleep(50);
	}
	return (0);
}

int	start_philo(t_data *philo_s)
{
	int	i;

	i = -1;
	philo_s->start_time = get_time(philo_s);
	while (++i < philo_s->philo_num)
	{
		start_routine(philo_s, i);
		usleep(1);
	}
	// monitor(philo_s);
	take_process(philo_s);
	return (0);
}

int	start_routine(t_data *philo_s, int id)
{
	pid_t	pid;
	t_philo	*philo;

	pid = fork();
	if (pid == 0)
	{
		philo = &philo_s->philos[id];
		philo->time_to_die = philo->data->death_time + get_time(philo->data);
		if (pthread_create(&philo->t1, NULL, supervisor, (void *)philo) != 0)
		{
			free_philo(philo->data);
			terminate_with_error(TH_CREATE, -4);
		}
		while (!is_alive(philo->data, 0))
		{
			eat(philo);
			message(THINK, philo);
		}
		pthread_join(philo->t1, NULL);
		exit (1);
	}
	else
		philo_s->pid[id] = pid;
	return (0);
}
