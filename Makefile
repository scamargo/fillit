# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scamargo <scamargo@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/30 21:11:57 by scamargo          #+#    #+#              #
#    Updated: 2017/12/12 22:22:26 by scamargo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libft.a
SRCS = fillit.c validations.c find_square.c

all:
	$(CC) -Wextra -Wall -Werror $(SRCS) -L. -lft -o fillit

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
