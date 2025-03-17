/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:48:03 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/17 19:28:32 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	message(char *str, t_philo *philo);
void	input_checker(int argc, char **argv);
uint64_t	get_time(t_data *philo_s);

void	message(char *str, t_philo *philo)
{
	uint64_t	time;

	sem_wait(philo->data->write);
	time = get_time(philo->data) - philo->data->start_time;
	if (ft_strcmp(str, DIED) == 0 && philo->data->dead == 0)
		printf("[TIME]: %lu [PHILO]: %d [ACTION]: %s\n", time, philo->id + 1, str);
	if (!philo->data->dead)
		printf("[TIME]: %lu [PHILO]: %d [ACTION]: %s\n", time, philo->id + 1, str);
	sem_post(philo->data->write);
}

uint64_t	get_time(t_data *philo_s)
{
	struct timeval	tv;
	uint64_t		cast_time;

	if (gettimeofday(&tv, NULL))
	{
		free_philo(philo_s);
		terminate_with_error(FAILED_GET_TIME, -3);
	}
	cast_time = (uint64_t)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (cast_time);
}

void	input_checker(int argc, char **argv)
{
	int		x;
	int		y;

	x = 1;
	y = 1;
	while (argv[x])
	{
		y = 0;
		while (argv[x][y])
		{
			if (argv[x][y] == ' ')
				(void)argc;
			else if (argv[x][y] < 48 || argv[x][y] > 57)
			{
				printf("%c | %d\n", argv[x][y], argv[x][y]);
				terminate_with_error(INVALID_FORMAT, -1);
			}
			y++;
		}
		x++;
	}
}

void	update_state(t_data *philo_s, int new_state)
{
	sem_wait(philo_s->lock);
	philo_s->dead = new_state;
	sem_post(philo_s->lock);
}

short	get_state(t_data *philo_s)
{
	int	state;

	sem_wait(philo_s->lock);
	state = philo_s->dead;
	sem_post(philo_s->lock);
	return (state);
}
