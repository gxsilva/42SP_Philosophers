/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_param_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:34:29 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/02/26 17:57:12 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <errno.h> //!REMOVE
#include <time.h> //!REMOVE

#ifndef thread_n
# define thread_n 10
#endif

int main(int argc, char **argv);
void *take_prime(void *arg);

int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

static void	exit_program(void)
{
	fprintf(stderr, "[Error] | FUNC: %s |[COD]: %d: MSG: %s\n", __func__, errno, strerror(errno));
	exit (errno);
}

void *take_prime(void *arg)
{
	int		nbr;

	nbr = *(int *)arg;
	printf("Value: %d\n", primes[nbr]);
	free(arg);
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t	th[thread_n];
	int			i;

	while(i < thread_n)
	{
		int		*nbr_pss;

		nbr_pss = (int *)malloc(sizeof(int *));
		*nbr_pss = i;
		/*
			The least argument pass in the pthread_create is the values that will
			be inputed in the function pass in the same function 

			because the time racing passa the value by address and trying acess
			thier values cause some stranger behaviors

			multi threading natural behavior
		*/
		// if (pthread_create(&th[i], NULL, take_prime, (void *)&i))
		if (pthread_create(&th[i], NULL, take_prime, (void *)nbr_pss)) 
		{
			i--;
			while (i != 0)
			{
				pthread_join(th[i], NULL);
				i--;
			}
			exit_program();
		}
		i++;
	}
	i = 0;
	while(i < thread_n)
	{
		if(pthread_join(th[i], NULL))
			exit_program();
		i++;
	}
	return (0);
}