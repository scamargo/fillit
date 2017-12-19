/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 22:09:23 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/18 21:09:37 by scamargo         ###   ########.fr       */
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

static char	**init_canvas(int side_length)
{
	char	**canvas;
	int		y;
	int		x;

	if(!(canvas = ft_init_chartable(side_length, side_length)))
		return (NULL);
	y = 0;
	while (y < side_length)
	{
		x = 0;
		while (x < side_length)
		{
			canvas[y][x] = '.';
			x++;
		}
		y++;
	}
	return (canvas);
}

static int	set_tetrimino_position(t_tet *tet, char **canvas_cpy, int side_length, int start[2])
{
	int y;
	int x;
	int r;
	int c;

	if ((side_length - start[1]) < tet->height || (side_length - start[0]) < tet->width)
		return (0);
	r = 0;
	y = start[1];
	while (r < tet->height)
	{
		c = 0;
		x = start[0];
		while (c < tet->width)
		{
			// TODO: check for conflicts before placing
			canvas_cpy[y][x] = tet->blocks[r][c];
			x++;
			c++;
		}
		y++;
		r++;
	}
	return (1);
}

static int	add_tetrimino(t_list *tets, char **canvas, int side_length)
{
	char	**canvas_cpy;
	int		y;
	int		x;
	int		start[2];

	y = 0;
	x = 0;
	// TODO: if piece width or height is bigger than side_length, return 0
	if (!(canvas_cpy = ft_memalloc(side_length * side_length)))
		return (0);
	while (y < side_length)
	{
		x = 0;
		while (x < side_length)
		{
			// reset canvas copy
			// TODO: verify this memmove is working
			start[0] = x;
			start[1] = y;
			canvas_cpy = ft_memmove(canvas_cpy, canvas, side_length * side_length);
			ft_putstr("set tetrimino at x: ");
			ft_putnbr(x);
			ft_putstr(", y: ");
			ft_putnbr(y);
			ft_putchar('\n');
			if (set_tetrimino_position((t_tet*)tets->content, canvas_cpy, side_length, start))
			{
				if (!tets->next)
				{
					// Yay! solution found
					print_square(canvas_cpy, side_length);
					free(canvas);
					free(canvas_cpy);
					return (1);
				}
				return (add_tetrimino(tets->next, canvas_cpy, side_length));
			}
			x++;
		}
		y++;
	}
	return (0);
}

int			find_square(t_list *tets)
{
	int		side_length;
	char	**canvas;

	side_length = 2;
	if(!(canvas = init_canvas(side_length)))
		return (0);
	ft_putstr("side_length: ");
	ft_putnbr(side_length);
	ft_putchar('\n');
	while (!add_tetrimino(tets, canvas, side_length))
	{
		free(canvas);
		if(!(canvas = init_canvas(++side_length)))
			return (0);
		ft_putstr("side_length: ");
		ft_putnbr(side_length);
		ft_putchar('\n');
	}
	// TODO: loop through unused tetriminos to find smallest square
	// TODO: make trimmed canvas two-dimensional array
	//canvas = trim_canvas(&canvas, width, height);
	//print_square(canvas, side_length);
	return (1);
}
