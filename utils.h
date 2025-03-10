/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:26:35 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/10 15:36:11 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*Includes*/
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>
# include "erros.h"

/*Definitions*/
# define DIED "died"
# define EATING "is eating"
# define TAKE_FORK "has taken a fork"
# define DROP_FORK "is sleeping"
# define THINK "is thinking"

/*Struct definitions*/
struct	s_philo;
struct	s_data;

/*Structures*/
typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*tid;
	t_philo			*philos;
	int				philo_num;
	int				meals_nb;
	int				dead;
	int				finished;
	uint64_t		death_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

int			ft_atoi(char *nbr);
int			ft_strlen(char *str);
int			ft_strcmp(char *str1, char *str2);
void		init_value(char **argv, int argc, t_data *philo_s);
void		free_philo(t_data *philo_s);
void		init_value(char **argv, int argc, t_data *philo_s);
void		message(char *str, t_philo *philo);
uint64_t	get_time(t_data *philo_s);
int			ft_usleep(uint64_t time, t_philo *philo);
void		input_checker(int argc, char **argv);
void		ft_exit(t_data *philo_s);
void		clear_data(t_data *philo_s);
void		terminate_with_error(char *str, int exit_cod);
void		*monitor(void *args);
void		*supervisor(void *args);
void		*routine(void *args);
void		eat(t_philo *philo);

#endif