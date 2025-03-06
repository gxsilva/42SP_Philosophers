/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettime_teste.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:57:15 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/05 20:37:01 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdint.h>

# define FAILED_GET_TIME "An unexpected error occurred gettimeofday"

static void	terminate_with_error(char *str, int exit_cod)
{
	printf("[Error]: %s\n", str);
	exit (exit_cod);
}

int main(void)
{
	struct timeval tv;
	struct timeval start, end;
	long	def_sec, def_mic_sec;
	uint64_t	res_cast;
	/*
		timval is struct with
		seconds && microsegundos
	*/

	if (gettimeofday(&tv, NULL)) //struct to time | time zone(OBSOLETO)
		terminate_with_error(FAILED_GET_TIME, -3);
	/* Retorna a quantidade de segundos desde de 1970 deinfido em
	primeiro de janeiro de 1970 cocmo o UTC(Coordinated Universal Time) */
	printf("Segundos: %ld\n", tv.tv_sec);
	printf("MicroSegundos: %ld\n", tv.tv_usec);
	
	// Calcular o tempo de execução de um programa
	if (gettimeofday(&start, NULL))
		terminate_with_error(FAILED_GET_TIME, -3);

	sleep(1);
	usleep(750000); //500 mil microsegundos é 0.5s
	
	if (gettimeofday(&end, NULL))
	terminate_with_error(FAILED_GET_TIME, -3);
	def_sec = end.tv_sec - start.tv_sec;
	def_mic_sec = end.tv_usec - start.tv_usec;

	/*
		Redistribuindo os valores que tenhamos as quantidades
		corretas de segundos e microsegundos
	*/
	if (def_mic_sec < 0)
	{
		def_sec--;
		def_mic_sec += 1000000;
	}
	printf("\n\nSECONDS: %ld\n", def_sec);
	printf("MICROSECONDS: %ld\n", def_mic_sec);

	/*
	Transformação de base
	segundos para milisegundos e microsegundos para milisegundos
	resultado vai ser o tempo total de diferença entra o inicio da medição
	e o final.
	*/
	res_cast = (uint64_t)(def_sec * 1000) + (uint64_t)(def_mic_sec / 1000);
	printf("DEF: %lu miliseconds\n", res_cast);
	return (0);
}