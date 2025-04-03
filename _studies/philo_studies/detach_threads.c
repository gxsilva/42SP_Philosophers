/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detach_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:56:45 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/05 20:52:56 by lsilva-x         ###   ########.fr       */
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


/*
	A função _pthread_detach_ serve para dar independencia a um thread
	pois ao passar uma thread como detach não é necessário utilizar pthread_join
	pois seus recursos sao liberados automáticamente quando ela termianr.
*/
static void	exit_program(void)
{
	fprintf(stderr, "[Error] | FUNC: %s |[COD]: %d: MSG: %s\n", __func__, errno, strerror(errno));
	exit (errno);
}

void	*routine(void *arg)
{
	printf("Thread Createded\n");
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t		th[thread_n];
	pthread_attr_t	attr; //iniciando um set de atributos
	int				i;

	//iniciando o set
	pthread_attr_init(&attr);
	//setando os atributos
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	//modes: Joinable or Detached
	while(i < thread_n)
	{
		/*
		O segundo parametro da função pthread_create se relaciona ao atributos
		da criação da thread como o modo dela
		*/
		if (pthread_create(&th[i], &attr, routine, NULL))
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
	// while(i < thread_n)
	// {
	// 	if(pthread_join(th[i], NULL))
	// 		exit_program();
	// 	i++;
	// }

	//desruindo os atributos da thread
	pthread_attr_destroy(&attr);
	return (0);
}