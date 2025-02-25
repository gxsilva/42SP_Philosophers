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

int main(int argc, char **argv)
{
	if (argc < 5)
	{
		printf("[Error]: Invalid numbers of arguments, minimum 4\n");
		return (-1);
	}
	return (0);
}
