/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 22:09:23 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/13 22:35:46 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// TODO: make canvas two-dimensional array
// TODO: create generic libft function for creating two-dimensional character array based on width & height
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

static char	*add_tetrimino(char *canvas, int *width, int *height)
{
	canvas[0] = 'A';
	canvas[1] = 'A';
	canvas[2] = 'A';
	canvas[17] = 'A';
	canvas[34] = 'B';
	canvas[35] = 'B';
	canvas[36] = 'B';
	canvas[37] = 'B';
	*width = 4;
	*height = 3;
	return (canvas);
}

char	*find_square(char *input)
{
	int		number_of_tetriminos;
	int		width;
	int		height;
	char	*canvas;

	number_of_tetriminos = 4; //TODO: remove!!
	if(!(canvas = init_canvas(number_of_tetriminos)))
		return (NULL);
	// TODO: loop through unused tetriminos to find smallest square
	canvas = add_tetrimino(canvas, &width, &height);
	// TODO: make trimmed canvas two-dimensional array
	//canvas = trim_canvas(&canvas, width, height);
	ft_strlen(input); //TODO: remove!!
	return (canvas);
}
