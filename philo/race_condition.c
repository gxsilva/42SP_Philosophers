/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   race_condition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:50:50 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/02/25 17:59:32 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/time.h> 
#include <pthread.h>

int	x = 0;

void	*routine(void *arg)
{
	int	i;

	i = 0;
	while(i <= 100000)
	{
		i++;
		x++;
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;

	if(pthread_create(&t1, NULL, &routine, NULL))
	{
		printf("[Error]: Create thread\n");
		return(-1);
	}
	if(pthread_create(&t2, NULL, &routine, NULL))
	{
		printf("[Error]: Create thread\n");
		return(-1);
	}	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("Value X: %d\n", x);
	return (0);
}
