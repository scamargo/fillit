# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scamargo <scamargo@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/30 21:11:57 by scamargo          #+#    #+#              #
#    Updated: 2017/12/29 15:12:18 by scamargo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
LIB = libft.a
LIB_SRCS = *.c
OBJS = $(LIB_SRCS:.c=.o)
NAME = fillit
SRCS = fillit.c validations.c find_square.c canvas_helper.c tetrimino_helper.c

all: $(NAME)

$(NAME): $(LIB)
	$(CC) -Wextra -Wall -Werror $(SRCS) -L. -lft -o $(NAME) -Ilibft

$(LIB):
	$(CC) -Wextra -Wall -Werror -c libft/$(LIB_SRCS)
	ar rc $(LIB) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIB)
	rm -f $(NAME)

re: fclean all
