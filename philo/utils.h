/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:26:35 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/05 18:55:32 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*Includes*/
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h> //struct timeval | gettimeofday
# include <pthread.h>
# include <stdint.h> //! REMOVE
# include "erros.h"

/*Definitions*/
struct s_philo;
struct s_data;

/*Structures*/
typedef struct s_philo
{
	struct s_data	*data; // pointer to the global structured shared by al the philo
	pthread_t		t1; // the individual thread of each philo
	int				id; // the identificator of each pihlo (0 -> philo_n - 1)
	int				eat_cont; // how many times this philo eat
	int				status; // the current state of the philo (eating, sleeping or dead)
	int				eating; // a flag to indicate if the philo is eating
	uint64_t		time_to_die; // ??
	pthread_mutex_t	lock; // the philo mutex
	pthread_mutex_t	*r_fork; // the right fork
	pthread_mutex_t	*l_fork; // the left fork
} t_philo;

typedef struct s_data // the main object
{
	pthread_t		*tid; // An array of each thread in the program
	t_philo			*philos; // An array of objects of each philo

	/*Informations*/
	int				philo_num; // how many philo are in the exectuion
	int				meals_nb; // number of meals of each philo must done until the program finish
	int				dead;	// ?? problay a flag to indicate if the philo is dead or alive
	int				finished; // ?? problay the number of philo that reach the limit of meals
	
	/*Time of each iteration */
	uint64_t		death_time; // time in miliseconds that each philo can dont meal until it dies
	uint64_t		eat_time; // time it takes a philosopher to eat
	uint64_t		sleep_time; // time it takes a philosopher to stay sleep
	uint64_t		start_time; // the initial time of the simulation

	/*Mutex stuffs */
	pthread_mutex_t	*forks; // Array of the mutex(forks) shared by the philoshopers
	pthread_mutex_t	lock; // ??
	pthread_mutex_t	write; // ??
} t_data;

/*LIBFT Functions*/
int		ft_atoi(char *nbr);
int		ft_strlen(char *str);

/*Functions*/
void	terminate_with_error(char *str, int exit_cod);
void	init_value(char **argv, int argc, t_data *philo_s);
void	free_philo(t_data *philo_s);
void	init_value(char **argv, int argc, t_data *philo_s);



#endif
