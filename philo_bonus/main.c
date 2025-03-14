/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:42:05 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/13 21:27:15 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int main(int argc, char **argv)
{
	t_data	philo_s;
	
	if (argc < 5 || argc > 6)
		terminate_with_error(INPUT_NUMBER, -1);
	input_checker(argc, argv);
	init_value(argv, argc, &philo_s);
	//* Handle with the single philo case
	// if (philo_s.philo_num == 1)
	// 	single_philo(&philo_s); 
	//else
	start_philo(&philo_s);
	return (0);
}

static void	*supervisor(void *args) // thought that is okay
{
	t_philo		*philo;

	philo = (t_philo *)args;
	while (philo->data->dead == 0)
	{
		sem_wait(philo->data->lock);
		if (get_time(philo->data) >= philo->time_to_die && philo->eating == 0)
			message(DIED, philo);
		else if (philo->eat_cont == philo->data->meals_nb)
		{
			sem_wait(philo->data->ph_lock);
			philo->data->finished++;
			philo->eat_cont++;
			sem_post(philo->data->ph_lock);
		}
		sem_post(philo->data->lock);
	}
	return (NULL);
}

static int	start_routine(t_data *philo_s, int id)
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
	while (philo->data->dead == 0)
	{
		eat(philo);
		message(THINK, philo);
	}
	if (pthread_join(philo->t1, NULL))
		return (0);
	}
	return (0);
}

int	start_philo(t_data *philo_s)
{
	int			i;
	pthread_t	t0;
	// t_philo		*crr;


	(void)t0;
	i = 0;
	philo_s->start_time = get_time(philo_s);
	// * it can be replaced by the i % 2== 0
	while (i < philo_s->philo_num)
	{
		start_routine(philo_s, i);
		i++;
	}
	i = 1;
	while (i < philo_s->philo_num)
	{
		start_routine(philo_s, i);
		i += 2;
	}
	return (0);
}