/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:26:08 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/06 15:00:56 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

static void	input_checker(int argc, char **argv);
static void	single_philo(t_data *philo_s);

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
	printf("Work\n");
}


//responsible to verify and update informations
static void *supervisor(void *args)
{
	t_philo		*philo;

	philo	= (t_philo *)args;
	//start the supervisor
	while (philo->data->dead == 0)
	{
		ptherad_mutex_lock(&philo->lock);
		if (get_time(philo->data) >= philo->time_to_die && philo->eating == 0)
			message(DIED, philo);
		else if (philo->eat_cont == philo->data->meals_nb)
		{
			ptherad_mutex_lock(&philo->data->lock);
			philo->data->finished++;
			philo->eat_cont++;
			ptherad_mutex_unlock(&philo->data->lock);
		} 
	}
	ptherad_mutex_unlock(&philo->lock);
	return (NULL);
}

static void	routine(void *args)
{
	t_philo		*philo;

	philo = (t_philo *)args;
	philo->time_to_die = philo->data->death_time + get_time(philo->data);
	if (ptherad_create(&philo->t1, NULL, supervisor, (void *)philo) != 0)
	{
		free_philo(philo->data);
		terminate_with_error(TH_CREATE, -4);
	}
	while (philo->data->dead == 0)
	{
		
	}
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
	//gives thread independence
	pthread_detach(&philo_s->tid[0]);
	// * UNDER CONSTRUCTION
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
