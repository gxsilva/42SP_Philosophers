/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:08:47 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/02/25 18:13:48 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/time.h> 
#include <pthread.h>

int	n_thread = 0;
int	x = 0;
pthread_mutex_t mutex;

void	*routine(void *arg)
{
	int	i = 0;
	n_thread++;
	printf("Thread %d create\n", n_thread);
	while(i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		x++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;

	pthread_mutex_init(&mutex, NULL); //ptr to mutex | ???
	if(pthread_create(&t1, NULL, routine, NULL))
	{
		printf("Error in create Thread %d\n", n_thread);
		return (-1);
	}
	if(pthread_create(&t2, NULL, routine, NULL))
	{
		printf("Error in create Thread %d\n", n_thread);
		return (-1);
	}
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_destroy(&mutex);
	printf("Value X: %d\n", x);
	return (0);
}
