/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:26:08 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/10 15:29:20 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

static void	single_philo(t_data *philo_s);
static int	many_philo(t_data *philo_s);

int	main(int argc, char **argv)
{
	t_data	philo_s;
	if (argc < 5 || argc > 6)
		terminate_with_error(INPUT_NUMBER, -1);
	input_checker(argc, argv);
	init_value(argv, argc, &philo_s);

	/*Handle with the case where has only one philo*/
	if (philo_s.philo_num == 1)
		single_philo(&philo_s);
	else
		many_philo(&philo_s);
	return (0);
}

int	many_philo(t_data *philo_s)
{
	int		i;
	pthread_t	t0;

	i = 0;
	philo_s->start_time = get_time(philo_s);
	if (philo_s->meals_nb > 0)
		if(pthread_create(&t0, NULL, &monitor, &philo_s->philos[0]))
			terminate_with_error(TH_CREATE, -4);
	while (i < philo_s->philo_num)
	{
		if(pthread_create(&philo_s->tid[i], NULL, &routine, (void *)&philo_s->philos[i]))
			terminate_with_error(TH_CREATE, -4);
		ft_usleep(1, &philo_s->philos[i]);
		i++;
	}
	i = 0;
	while (i < philo_s->philo_num)
	{
		if (pthread_join(philo_s->tid[i], NULL))
			terminate_with_error(TH_JOIN, -4);
		i++;
	}
	return (0);
}

static void	single_philo(t_data *philo_s)
{
	philo_s->start_time = get_time(philo_s);
	/*Thread ptr, set attr, routine, parms */
	if (pthread_create(&philo_s->tid[0], NULL, &routine, &philo_s->philos[0]))
	{
		free_philo(philo_s);
		terminate_with_error(TH_CREATE, -4);
	}
	pthread_detach(philo_s->tid[0]);
	while (philo_s->dead == 0)
		ft_usleep(0, &philo_s->philos[0]);
	ft_exit(philo_s);
}
