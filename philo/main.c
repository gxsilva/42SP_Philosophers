/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:26:08 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/06 18:23:44 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

static void	input_checker(int argc, char **argv);
static void	single_philo(t_data *philo_s);
int	init_philo(t_data *philo_s);

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
		init_philo(&philo_s);
	return (0);
}

static void *monitor(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->data->finished >= philo->data->philo_num)
			philo->data->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return (NULL);
}

int	init_philo(t_data *philo_s)
{
	int		i;
	pthread_t	t0;

	i = 0;
	philo_s->start_time = get_time(philo_s);
	if (philo_s->meals_nb > 0)
		if(pthread_create(&t0, NULL, monitor, &philo_s->philos[0]))
			terminate_with_error(TH_CREATE, -4);
	while (i < philo_s->philo_num)
	{
		printf("aa\n");
		if(pthread_create(&philo_s->tid[i], NULL, routine, &philo_s->philos[i]))
			terminate_with_error(TH_CREATE, -4);
		ft_usleep(1, &philo_s->philos[i]);
		i++;
	}
	i = 0;
	while (i < philo_s->philo_num)
	{
		if (pthread_join(philo_s->tid[i], NULL))
			terminate_with_error(TH_JOIN, -4);
	}
	return (0);
}

//responsible to verify and update informations
static void *supervisor(void *args)
{
	t_philo		*philo;

	philo	= (t_philo *)args;
	//start the supervisor
	while (philo->data->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time(philo->data) >= philo->time_to_die && philo->eating == 0)
			message(DIED, philo);
		else if (philo->eat_cont == philo->data->meals_nb)
		{
			pthread_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->eat_cont++;
			pthread_mutex_unlock(&philo->data->lock);
		} 
	}
	pthread_mutex_unlock(&philo->lock);
	return (NULL);
}

void	*routine(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
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
		return (NULL);
	return (NULL);
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

static void	input_checker(int argc, char **argv)
{
	int		x;
	int		y;

	x = 1;
	y = 1;
	while (argv[x])
	{
		y = 0;
		while(argv[x][y])
		{
			if (argv[x][y] == ' ')
				(void)argc;
			else if(argv[x][y] < 48 || argv[x][y] > 57)
			{
				printf("%c | %d\n", argv[x][y], argv[x][y]);
				terminate_with_error(INVALID_FORMAT, -1);
			}
			y++;
		}
		x++;
	}
}
