/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:26:08 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/02/26 20:38:34 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

long int take_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_usec);
}

float

int main(int argc, char **argv)
{
	long		x;
	long		y;

	x = take_time();
	for (volatile long i = 0; i < 1000000; i++);
	y = take_time();
	printf("Time pass: %ld\n", y - x);
	return (0);
}
/*
int main(int argc, char **argv)
{
	int		init_time;
	int		end_time;
	
	printf("Init time: %d\n", init_time);
	sleep(5);
	gettimeofday(&tv, NULL); //atualizar os valores após sleep
	end_time = tv.tv_sec;
	printf("Final time: %d\n", end_time);
	printf("Time: %d\n", (end_time - init_time));
	printf("Seconds: %lu\n", tv.tv_sec);
	printf("Miliseconds: %lu\n", tv.tv_usec);
	return (0);
}
*/