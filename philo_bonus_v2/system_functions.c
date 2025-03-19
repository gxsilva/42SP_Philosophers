/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:14:11 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/19 03:02:20 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*supervisor(void *args);
int		start_routine(t_data *philo_s, int id);
int		monitor(t_data *philo_s);
int		start_philo(t_data *philo_s);
int		take_process(t_data *philo_s);

void	*supervisor(void *args) //? okay
{
	t_philo		*philo;

	philo = (t_philo *)args;
	while (1)
	{
		if (get_time(philo->data) >= philo->time_to_die)
		{
			update_state(philo->data, 1);
			message(DIED, DIED, philo);
			// sem_wait(philo->data->s_write);
			break;
		}
		usleep(10);
	}
	return (NULL);
}

int	start_routine(t_data *philo_s, int id)
{
	pid_t	pid;
	t_philo	*philo;

	philo = &philo_s->philos[id];
	pid = fork();
	if (pid == 0)
	{
		philo->time_to_die = philo->data->death_time + get_time(philo->data);
		if (pthread_create(&philo->t1, NULL, supervisor, (void *)philo))
		{
			free_philo(philo->data);
			terminate_with_error(TH_CREATE, -4);
		}
		while (!get_state(philo->data))
		{
			if(philo->data->meals_nb > -1)
				if (philo->eat_cont >= philo->data->meals_nb)
					exit (0);
			if (take_forks(philo))
				break ;
			if(eat(philo))
			{
				drop_forks(philo);
				break ;
			}
			drop_forks(philo);
			sleep_ph(philo);
			// if (philo->data->philo_num % 2 != 0)
			// 	think_ph(philo);
		}
		pthread_join(philo->t1, NULL);
		exit (1);
	}
	philo->pid = pid;
	philo_s->pid[id] = pid;
	return (0);
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
		i = 0;
		while (i < philo_s->philo_num)
		{
			if (waitpid(philo_s->philos[i].pid, &status, WNOHANG) > 0)
			{
				if (WEXITSTATUS(status) == 1)
					return(kill_process(philo_s), 1);
				else if (WEXITSTATUS(status) == 0)
					finished++;
			}
			i++;
		}
		if (philo_s->philo_num == finished)
			return (kill_process(philo_s), 1);
		usleep(80);
	}
	return (0);
}

int	take_process(t_data *philo_s)
{
	int	i;
	int	status;

	i = 0;
	while (i < philo_s->philo_num)
	{
		waitpid(philo_s->philos[i].pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				kill_process(philo_s);
				break ;
			}
		}
		i++;
	}
	return (0);
}

int	start_philo(t_data *philo_s)
{
	int	i;

	i = 0;
	philo_s->start_time = get_time(philo_s);
	while (i < philo_s->philo_num)
	{
		start_routine(philo_s, i);
		i += 2;
	}
	i = 1;
	while (i < philo_s->philo_num)
	{
		start_routine(philo_s, i);
		i += 2;
	}
	monitor(philo_s);
	take_process(philo_s);
	return (0);
}
