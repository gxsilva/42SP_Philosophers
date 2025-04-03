/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_in_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:53:05 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/02/26 19:26:06 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

#define th_n 4

int		x = 0;
pthread_mutex_t mutex_a;

void	*routine(void *arg)
{
	int		i;

	i = 0;
	while (i < 100000)
	{
		pthread_mutex_lock(&mutex_a);
		x++;
		pthread_mutex_unlock(&mutex_a);
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	int		i;
	pthread_t th[th_n]; //create an array with 4 diffrent threads

	if(pthread_mutex_init(&mutex_a, NULL))
	{
		perror("Cannot create Mutex\n");
		return (-1);
	}
	i = 0;
	
	while(i < 4) //A loop to create each thread
	{
		if (pthread_create(&th[i], NULL, &routine, NULL)) // handle with erros
		{
			perror("Cannot create\n");
			i--;
			while (i != 0) // await all threadh done their task before end the program
				pthread_join(th[i], NULL);
			return (-2);
		}
		i++;
	}
	i = 0;
	/*
		the correct behavior to allow all threads run separately is
		join their after the creatin in another loop.
	*/
	while(i < th_n)
	{
		if(pthread_join(th[i], NULL))
		{
			perror("Pthread_join error\n");
			return (-3);
		}
		i++;
	}
	pthread_mutex_destroy(&mutex_a); // destroy de mutex before the pthread_join
	printf("Value X: %d\n", x);
	return (0);
}