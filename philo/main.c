/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:26:08 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/06 16:19:42 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

static int	_single_philo(t_data *philo_s);
static int	_start_philo(t_data *philo_s);

int	main(int argc, char **argv)
{
	t_data	philo_s;
	int		cod;

	if (argc < 5 || argc > 6)
		return (terminate_with_error(INPUT_NUMBER, -1));
	if (!input_checker(argv))
		return (terminate_with_error(INVALID_FORMAT, -1));
	if (!init_value(argv, argc, &philo_s, &cod))
	{
		if (cod == 1)
			return (terminate_with_error(PHI_OUT_RANGE, -1));
		else
			return (terminate_with_error(FAILED_MALLOC, -2));
	}
	if (philo_s.philo_num == 1)
	{
		if (_single_philo(&philo_s) == 0)
			return (terminate_with_error(TH_CREATE, -4));
	}
	else
		_start_philo(&philo_s);
	free_philo(&philo_s);
	return (0);
}

static int	_start_philo(t_data *philo_s)
{
	int			i;
	pthread_t	t0;
	t_philo		*crr;

	i = -1;
	t0 = 0;
	philo_s->start_time = get_time(philo_s);
	if (philo_s->meals_nb > 0)
		if (pthread_create(&t0, NULL, monitor, &philo_s->philos[0]))
			return (terminate_with_error(TH_CREATE, -4));
	while (++i < philo_s->philo_num)
	{
		crr = &philo_s->philos[i];
		if (pthread_create(&philo_s->tid[i], NULL, routine, crr))
			terminate_with_error(TH_CREATE, -4);
		ft_usleep(1, &philo_s->philos[i]);
	}
	i = -1;
	while (++i < philo_s->philo_num)
		if (pthread_join(philo_s->tid[i], NULL))
			return (terminate_with_error(TH_JOIN, -4));
	if (t0)
		pthread_join(t0, NULL);
	return (0);
}

static int	_single_philo(t_data *philo_s)
{
	t_philo		*s_ph;

	philo_s->start_time = get_time(philo_s);
	s_ph = &philo_s->philos[0];
	s_ph->time_to_die = philo_s->death_time - get_time(philo_s);
	pthread_mutex_lock(s_ph->l_fork);
	message(TAKE_FORK, s_ph);
	pthread_mutex_unlock(s_ph->l_fork);
	ft_usleep(philo_s->death_time, s_ph);
	message(DIED, s_ph);
	return (1);
}

// static int	_single_philo(t_data *philo_s)
// {
// 	philo_s->start_time = get_time(philo_s);
// 	if (pthread_create(&philo_s->tid[0], NULL, &routine, &philo_s->philos[0]))
// 		return (0);
// 	pthread_detach(philo_s->tid[0]);
// 	while (philo_s->dead == 0)
// 		ft_usleep(0, &philo_s->philos[0]);
// 	free_philo(philo_s);
// 	return (1);
// }
