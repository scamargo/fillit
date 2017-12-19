/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 22:09:23 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/18 16:23:22 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

static void	print_square(char **canvas, int side_length)
{
	int y;
	int x;

	y = 0;
	while (y < side_length)
	{
		x = 0;
		while (x < side_length)
		{
			ft_putchar(canvas[y][x]);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}

static char	**init_canvas(int *side_length)
{
	char	**canvas;
	int		y;
	int		x;

	if(!(canvas = ft_init_chartable(*side_length, *side_length)))
		return (NULL);
	y = 0;
	while (y < *side_length)
	{
		x = 0;
		while (x < *side_length)
		{
			canvas[y][x] = '.';
			x++;
		}
		y++;
	}
	return (canvas);
}

static char	**add_tetrimino(char **canvas, int *side_length, t_list *tets)
{
	// TODO: use width & height passed in to iterate through table
	int max_width;
	int max_height;
	canvas[0][0] = 'A';
	canvas[0][1] = 'A';
	canvas[0][2] = 'A';
	canvas[1][0] = 'A';
	canvas[2][0] = 'B';
	canvas[2][1] = 'B';
	canvas[2][2] = 'B';
	canvas[1][2] = 'B';
	max_width = 3;
	max_height = 3;
	*side_length = (max_width > max_height) ? max_width : max_height;
	//print_square((char**)((t_tet*)tets->content)->blocks, 4); //TODO: remove after testing
	((t_tet*)tets->content)->used = 0; 
	return (canvas);
}

int			find_square(t_list *tets, short number_of_tets)
{
	int		side_length;
	char	**canvas;

	side_length = number_of_tets * 4;
	if(!(canvas = init_canvas(&side_length)))
		return (0);
	// TODO: loop through unused tetriminos to find smallest square
	canvas = add_tetrimino(canvas, &side_length, tets);
	// TODO: make trimmed canvas two-dimensional array
	//canvas = trim_canvas(&canvas, width, height);
	print_square(canvas, side_length);
	return (1);
}
