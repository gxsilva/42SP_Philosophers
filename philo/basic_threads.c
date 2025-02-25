/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:30:21 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/02/24 20:38:44 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //malloc, free 
#include <unistd.h> //write, usleep
#include <sys/time.h> //gettimeofday
#include <pthread.h> //pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy,pthread_mutex_lock, pthread_mutex_unlock

void	*routine(void *arg)
{
	printf("Hi\n");
	sleep(2);
	if (!(char *)arg)
		printf("Hello generic\n");
	else
		printf("Hello %s\n", (char *)arg);
	return NULL;
}
int main(int argc, char **argv)
{
	pthread_t	t2;
	pthread_t	t1;

	char		*msg = "Linus";
	
	if(pthread_create(&t2, NULL, routine, (void *)msg) != 0)
	{
		printf("Error in create thread\n");
		return (-1);
	}

	if(pthread_create(&t1, NULL, routine, NULL) != 0)
	{	
		printf("Error in create thread\n");
		pthread_join(t2, NULL); //thread | pointer to get result (if it has)
		return (-2);
	}//pointer to thread | attributes(customization) | function will execute whend it creates | args to the function
	//wait for thread terminate
	pthread_join(t1, NULL); //thread | pointer to get result (if it has)
	pthread_join(t2, NULL);

	return (0);
}
