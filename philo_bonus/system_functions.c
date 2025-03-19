/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:14:11 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/18 23:40:45 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*supervisor(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	while (!get_state(philo->data))
	{
		if (get_time(philo->data) >= philo->time_to_die && philo->eating == 0)
		{
			update_state(philo->data, 1);
			message(DIED, philo);
			break;
		}
		usleep(10);
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
		// usleep(50);
	}
	return (0);
}

int	start_philo(t_data *philo_s)
{
	int	i;

	i = -1;
	philo_s->start_time = get_time(philo_s);
	while (++i < philo_s->philo_num)
		start_routine(philo_s, i);
	// monitor(philo_s);
	printf("take process\n");
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
		while (get_state(philo->data) != 1)
		{
			eat(philo);
			message(THINK, philo);
		}
		pthread_join(philo->t1, NULL);
		exit (1);
	}
	philo_s->pid[id] = pid;
	return (0);
}
