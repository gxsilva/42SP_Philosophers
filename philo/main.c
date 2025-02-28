/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:26:08 by lsilva-x          #+#    #+#             */
/*   Updated: 2025/02/28 18:34:41 by lsilva-x         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./utils.h"

static void	input_checker(int argc, char **argv);

int	main(int argc, char **argv)
{
	t_data	philo_s;
	if (argc < 5 || argc > 6)
		terminate_with_error(INPUT_NUMBER, -1);
	input_checker(argc, argv);
	init_value(argv, argc, &philo_s);
	printf("Work\n");
}

static void	input_checker(int argc, char **argv)
{
	int		x;
	int		y;

	x = 1;
	y = 1;
	while (argv[x])
	{
		y = 0;
		while(argv[x][y])
		{
			if (argv[x][y] == ' ')
				(void)argc;
			else if(argv[x][y] < 48 || argv[x][y] > 57)
			{
				printf("%c | %d\n", argv[x][y], argv[x][y]);
				terminate_with_error(INVALID_FORMAT, -1);
			}
			y++;
		}
		x++;
	}
}
