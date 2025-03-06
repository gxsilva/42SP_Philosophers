/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:26:08 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/05 21:04:09 by lsilva-x         ###   ########.fr       */
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

static uint64_t	get_time(t_data *philo_s)
{
	struct timeval	tv;
	uint64_t		cast_time;
	
	if (gettimeofday(&tv, NULL))
	{
		free_philo(philo_s);
		terminate_with_error(FAILED_GET_TIME, -3);
	}
	cast_time = (uint64_t)((tv.tv_sec * 1000) / (tv.tv_usec / 1000));
	return (cast_time);
}

static void	routine(void *args)
{
	/*args is the philo ptr*/
	
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
