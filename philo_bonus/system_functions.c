/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:14:11 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/08 17:53:13 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		start_philo(t_data *philo_s);
int		start_routine(t_data *philo_s, int id);
void	take_process(t_data *philo_s);

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
		while (philo->eat_cont != 0)
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

void	take_process(t_data *philo_s)
{
	int	i;
	int	status;

	i = -1;
	while (++i < philo_s->philo_num)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) == EXIT_FAILURE)
				return (kill_process(philo_s));
	}
}

