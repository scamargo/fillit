/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 22:09:23 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/13 21:39:43 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*init_canvas(int num_of_tetriminos)
{
	int		side_length;
	char	*canvas;
	int		i;

	side_length = (num_of_tetriminos * 4);
	if(!(canvas = ft_memalloc((side_length + 1) * side_length + 1)))
	   return (NULL);
	i = 0;
	while (i < ((side_length + 1) * side_length))
	{
		if (i % (side_length + 1) == side_length)
			canvas[i] = '\n';
		else
			canvas[i] = '.';
		i++;
	}
	canvas[i] = '\0';
	return (canvas);
}					

char	*find_square(char *input)
{
	int		number_of_tetriminos;
	char	*canvas;

	number_of_tetriminos = 4; //TODO: remove!!
	if(!(canvas = init_canvas(number_of_tetriminos)))
		return (NULL);
	//trim_canvas(&canvas);
	ft_strlen(input); //TODO: remove!!
	return (canvas);
}
