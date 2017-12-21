# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scamargo <scamargo@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/30 21:11:57 by scamargo          #+#    #+#              #
#    Updated: 2017/12/20 21:39:01 by scamargo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
LIB = libft.a
LIB_SRCS = libft/*.c
OBJS = $(LIB_SRCS:.c=.o)
SRCS = fillit.c validations.c find_square.c

all:
	$(CC) -Wextra -Wall -Werror -g $(SRCS) -L. -lft -o fillit -Ilibft

$(LIB):
	$(CC) -Wextra -Wall -Werror -c $(LIB_SRCS)
	mv *.o libft/
	ar rc $(LIB) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIB)

re: fclean all
