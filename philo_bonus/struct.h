/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:43:03 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/17 17:40:03 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCT_H
# define  STRUCT_H

#include "utils.h"

# define SEM_FORKS "forks"
# define SEM_LOCKS "lock"
# define SEM_WRITE "write"
# define SEM_PH_LOCK "ph_lock"

struct s_philo;
struct s_data;

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	pthread_t		t1; // monitor | must be a thread
	pid_t			pid;
	int				eat_cont;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	// sem_t	lock;
	// sem_t	*r_fork;
	// sem_t	*l_fork;
}	t_philo;


typedef struct s_data
{
	pid_t			*pid;
	t_philo			*philos;
	int				philo_num;
	int				meals_nb;
	volatile int				dead;
	int				finished;
	uint64_t		death_time;
	uint64_t		eat_time;
	uint64_t		sleep_time;
	uint64_t		start_time;
	sem_t	*forks;
	sem_t	*lock;
	sem_t	*ph_lock;
	sem_t	*write;
}	t_data;

# endif
