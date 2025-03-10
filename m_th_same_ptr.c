/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_th_same_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 00:00:47 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/09 20:02:53 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h> 
# include <pthread.h>
# include <stdint.h>

# define TH_CREATE "Thread creation"

static void	terminate_with_error(char *str, int exit_cod);
static void *routine(void *args);


static void *routine(void *args)
{
	int		*res;

	res = (int *)args;
	printf("Thread Created: %d\n", *res);
	return (NULL);
}

static void	terminate_with_error(char *str, int exit_cod)
{
	printf("[Error]: %s\n", str);
	exit (exit_cod);
}

int main(void)
{
	pthread_t	t1;
	int		i;

	i = 0;
	if (pthread_create(&t1, NULL, &routine, (void *)&i) != 0);
		terminate_with_error(TH_CREATE, -1);
	pthread_detach(t1);
	i++;
	if (pthread_create(&t1, NULL, &routine, (void *)&i) != 0);
		terminate_with_error(TH_CREATE, -1);
	pthread_detach(t1);
	return (0);
}