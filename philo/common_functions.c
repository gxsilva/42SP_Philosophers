/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:45:18 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/02/27 14:45:35 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_atoi(char *nbr)
{
	int		i;
	int		signal;
	int		res;

	i = 0;
	res = 0;
	signal = 1;
	if (nbr[i] == '+' || nbr[i] == '-')
	{
		if (nbr[i] == '-')
			signal = -1;
		if (nbr[i + 1] < '0' || nbr[i + 1] > '9')
		{
			printf("[Error]: Invalid input format or number of inputs\n");
			exit (-1);
		}
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		res = (res * 10) + nbr[i] - '0';
		i++;
	}
	return (res * signal);
}