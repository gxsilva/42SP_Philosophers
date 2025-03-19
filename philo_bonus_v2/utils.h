/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:42:45 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/19 02:58:56 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <stdint.h>
# include <fcntl.h>
# include "erros.h"
# include "struct.h"

# define DIED "died"
# define EATING "is eating"
# define TAKE_FORK "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"

void		input_checker(int argc, char **argv);
void		init_value(char **argv, int argc, t_data *philo_s);
int			start_philo(t_data *philo_s);

/* Philo Actions */
int			eat(t_philo *philo);
int			take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);
int			sleep_ph(t_philo *philo);
int			think_ph(t_philo *philo);

/*same error functions*/
void		terminate_with_error(char *str, int exit_cod);
void		free_philo(t_data *philo_s);
void		clear_data(t_data *philo_s);
void		ft_exit(t_data *philo_s);

/*same lib functions */
int			ft_atoi(char *nbr);
int			ft_strlen(char *str);
int			ft_strcmp(char *str1, char *str2);
int			ft_usleep(uint64_t time, t_philo *philo);

/*Common functions */
void		message(char *str, char *log, t_philo *philo);
void		input_checker(int argc, char **argv);
uint64_t	get_time(t_data *philo_s);
void		update_state(t_data *philo_s, int new_state);
short		get_state(t_data *philo_s);

/* idk functions */
int			start_routine(t_data *philo_s, int id);
void		*supervisor(void *args);
int			monitor(t_data *philo_s);
int			take_process(t_data *philo_s);
int			start_philo(t_data *philo_s);
int			kill_process(t_data *philo_s);

#endif
