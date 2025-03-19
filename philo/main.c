/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:26:08 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/19 01:48:10 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

static void	single_philo(t_data *philo_s);
static int	start_philo(t_data *philo_s);

int	main(int argc, char **argv)
{
	t_data	philo_s;

	if (argc < 5 || argc > 6)
		terminate_with_error(INPUT_NUMBER, -1);
	input_checker(argc, argv);
	init_value(argv, argc, &philo_s);
	if (philo_s.philo_num == 1)
		single_philo(&philo_s);
	else
		start_philo(&philo_s);
	free_philo(&philo_s);
	return (0);
}

int	start_philo(t_data *philo_s)
{
	int			i;
	pthread_t	t0;
	t_philo		*crr;

	i = 0;
	t0 = 0;
	philo_s->start_time = get_time(philo_s);
	if (philo_s->meals_nb > 0)
		if (pthread_create(&t0, NULL, monitor, &philo_s->philos[0]))
			terminate_with_error(TH_CREATE, -4);
	while (i < philo_s->philo_num)
	{
		crr = &philo_s->philos[i];
		if (pthread_create(&philo_s->tid[i], NULL, routine, crr))
			terminate_with_error(TH_CREATE, -4);
		ft_usleep(1, &philo_s->philos[i]);
		i++;
	}
	i = -1;
	while (++i < philo_s->philo_num)
		if (pthread_join(philo_s->tid[i], NULL))
			terminate_with_error(TH_JOIN, -4);
	if (t0)
		pthread_join(t0, NULL);
	return (0);
}

static void	single_philo(t_data *philo_s)
{
	philo_s->start_time = get_time(philo_s);
	if (pthread_create(&philo_s->tid[0], NULL, &routine, &philo_s->philos[0]))
		terminate_with_error(TH_CREATE, -4);
	pthread_detach(philo_s->tid[0]);
	while (philo_s->dead == 0)
		ft_usleep(0, &philo_s->philos[0]);
	free_philo(philo_s);
}
