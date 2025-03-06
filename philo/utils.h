/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:26:35 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/06 16:04:32 by lsilva-x         ###   ########.fr       */
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
# define DIED "died"
# define EATING "is eating"
# define TAKE_FORK "has taken a fork"
# define DROP_FORK "is sleeping"
# define THINK "is thinking"

/*Struct definitions*/
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
	int				eating; // a flag to indicate if the philo is eating(1) OR NOT (0)
	uint64_t		time_to_die; // the time this philo will die if it not will eat
	pthread_mutex_t	lock; // the mutex to prevent "race condition"
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
	int				dead;	// 0 = any philo dies | if anyone dies the program stop
	int				finished; // if the philo has a amout of meals
	
	/*Time of each iteration */
	uint64_t		death_time; // time in miliseconds that each philo can dont meal until it dies
	uint64_t		eat_time; // time it takes a philosopher to eat
	uint64_t		sleep_time; // time it takes a philosopher to stay sleep
	uint64_t		start_time; // the initial time of the simulation

	/*Mutex stuffs */
	pthread_mutex_t	*forks; // Array of the mutex(forks) shared by the philoshopers
	pthread_mutex_t	lock; // A mutex to prevent "race condition"
	pthread_mutex_t	write; // ??
} t_data;

/*LIBFT Functions*/
int			ft_atoi(char *nbr);
int			ft_strlen(char *str);
int			ft_strcmp(char *str1, char *str2);

/*Functions*/
void		init_value(char **argv, int argc, t_data *philo_s);
void		free_philo(t_data *philo_s);
void		init_value(char **argv, int argc, t_data *philo_s);
void		message(char *str, t_philo *philo);
uint64_t	get_time(t_data *philo_s);
int			ft_usleep(uint64_t time, t_philo *philo);

/*Exit functions */
void		ft_exit(t_data *philo_s);
void		clear_data(t_data *philo_s);
void		terminate_with_error(char *str, int exit_cod);

/*Actions functions */
void		*routine(void *args);
void		eat(t_philo *philo);


#endif
 