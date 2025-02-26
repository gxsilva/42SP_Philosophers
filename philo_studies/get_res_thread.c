/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_res_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:41:33 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/02/26 15:19:19 by lsilva-x         ###   ########.fr       */
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

void	exit_errno(void)
{
		fprintf(stderr, "[Error] | FUNC: %s |[COD]: %d: MSG: %s\n", errno, __func__, strerror(errno));
		exit (errno);
}

void	*roll_dice(void *arg)
{
	/*
		whend the values are returnde is importan to pay attetion of the type
		of the variable, if it's lcaol variable it's gonna be desalocated in
		the end of the stack(end of the function), to can returna value from 
		inside a function is correct do dynmicallt allocat the value
	*/
	int	rand_nbr;
	int	*res_f = (int *)malloc(sizeof(int *));

	rand_nbr = (rand() % 6) + 1; // a value between 1 and 6
	// printf("Rand Nbr: %d\n", rand_nbr);
	*res_f = rand_nbr;
	return (res_f);
}

int main(int arc, char **argv)
{
	pthread_t	t1;
	int			*res_t1;
	
	//init rand??
	srand(time(NULL));
	if (pthread_create(&t1, NULL, roll_dice, NULL))
		exit_errno();
	/*
	the second value from join is a pointer to another pointer that basic gonna
	set the res value from that thread process and put it into that pointer;
	*/
	if (pthread_join(t1, (void **)&res_t1))
		exit_errno();
	printf("Rand val: %d\n", *res_t1);
	free(res_t1); // freee the ptr res_t1
	return (0);
}