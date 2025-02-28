/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:45:18 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/02/28 15:14:55 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	terminate_with_error(char *str, int exit_cod)
{
	printf("[Error]: %s\n", str);
	exit (exit_cod);
}

/*
Talvez isso de problema pois a alocação de estrutura na main não é com callo
ent nem sempre a comparação vai ser NULL para que possamo pular algum freee
podendo ocasionar em doublee free ou undefined Behavior
*/
void	free_philo(t_data *philo_s) 
{
	int i;

	if (philo_s == NULL)
		return ;
	(&philo_s->lock);
	pthread_mutex_destroy(&philo_s->write);
	if (philo_s->forks != NULL) {
		i = 0;
		while (i < philo_s->philo_num) {
			pthread_mutex_destroy(&philo_s->forks[i]);
			i++;
		}
		free(philo_s->forks);
		philo_s->forks = NULL;
	}
	if (philo_s->philos != NULL) {
		i = 0;
		while (i < philo_s->philo_num) {
			pthread_mutex_destroy(&philo_s->philos[i].lock);
			i++;
		}
		free(philo_s->philos);
		philo_s->philos = NULL;
	}
	if (philo_s->tid != NULL) {
		free(philo_s->tid);
		philo_s->tid = NULL;
	}
	free(philo_s);
}