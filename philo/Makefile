# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsilva-x <lsilva-x@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/27 14:47:36 by lsilva-x          #+#    #+#              #
#    Updated: 2025/03/06 21:12:50 by lsilva-x         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
NAME	= philo
CFLAG	= -Wall -Wextra -Werror -W -pthread -Wunreachable-code -Ofast -g

SRC		=	main.c \
			common_functions.c \
			libft_functions.c \
			init_value.c \
			actions.c \
			erros_functions.c \
			system_functions.c

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