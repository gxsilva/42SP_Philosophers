/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:26:44 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/10 19:48:19 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

sem_t sem; // ! Global variable are not allow

//example of a shared function
void	*func(void *args)
{
	sem_wait(&sem); // as the same of pthread_mutex_lock | if the entries are 0
	printf("Thread %s is execution\n", (char *)args);
	sem_post(&sem); // As the same of pthread_mutex_unlock | open an entrie on the semaphore
	return ((void *)NULL);
}

int main(int argc, char **argv)
{
	
	sem_init(&sem , 0, 1); //semaphore | shared threads | entreies in the semaphore
	/*
	Shared Threads
	0 -> threads from the same process
	1 -> diferent process
	*/
	func("Hello World");
	sem_destroy(&sem); // as the same of pthread_mutex_destroy

	return (0);
}