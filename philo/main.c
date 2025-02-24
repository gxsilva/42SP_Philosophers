/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:30:21 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/02/24 20:35:00 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

int main(int argc, char **argv)
{
	if (argc < 5)
	{
		printf("[Error]: Invalid numbers of arguments, minimum 4\n");
		return (-1);
	}
	return (0);
}
