# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/27 14:47:36 by lsilva-x          #+#    #+#              #
#    Updated: 2025/04/08 15:23:22 by lsilva-x         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
NAME	= philo_bonus
CFLAG	= -Wall -Wextra -Werror -W -pthread -g

SRC		=	main.c \
			common_functions.c \
			libft_functions.c \
			init_value.c \
			actions.c \
			erros_functions.c \
			system_functions.c \
			utils_bonus.c

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re