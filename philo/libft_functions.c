/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 13:24:44 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/03/06 15:03:07 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		ft_atoi(char *nbr);
int		ft_strlen(char *str);
int		ft_strcmp(char *str1, char *str2);

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

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *str1, char *str2)
{
	int		i;
	
	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (((unsigned char)str1[i] - (unsigned char)str2[i]));
}

int	ft_usleep(useconds_t time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}