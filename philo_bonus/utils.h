/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:42:45 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/04/08 17:26:01 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>
# include <stdint.h>
# include <fcntl.h>
# include "erros.h"
# include "struct.h"

# define DIED "died"
# define EATING "is eating"
# define TAKE_FORK "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"

void		input_checker(char **argv);
void		init_value(char **argv, int argc, t_data *philo_s);
int			start_philo(t_data *philo_s);
void		eat(t_philo *philo);

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
void		message(char *str, t_philo *philo);
uint64_t	get_time(t_data *philo_s);
int			is_alive(t_data *philo_s, int mod);

/* idk functions */
int			start_routine(t_data *philo_s, int id);
// void		*supervisor(void *args);
// int			monitor(t_data *philo_s);
void		take_process(t_data *philo_s);
int			start_philo(t_data *philo_s);
void		kill_process(t_data *philo_s);
void		close_semaphore(t_data *philo_s);

#endif
