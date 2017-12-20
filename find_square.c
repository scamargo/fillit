/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 22:09:23 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/19 18:40:36 by scamargo         ###   ########.fr       */
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

static int	set_tetrimino_position(t_tet *tet, char **canvas, int side_length, int start[2])
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
			if (canvas[y][x] != '.' && tet->blocks[r][c] != '.')
				return (0);
			if(tet->blocks[r][c] != '.')
				canvas[y][x] = tet->blocks[r][c];
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
	int		i;

	y = 0;
	x = 0;
	if (((t_tet*)tets->content)->width > side_length || ((t_tet*)tets->content)->height > side_length)
		return (0);
	if(!(canvas_cpy = ft_init_chartable(side_length, side_length)))
		return (0);
	while (y < side_length)
	{
		x = 0;
		while (x < side_length)
		{
			start[0] = x;
			start[1] = y;
			i = 0;
			while (i < side_length)
			{
				ft_memmove(canvas_cpy[i], canvas[i], side_length);
				i++;
			}
			//print_square(canvas_cpy, side_length);
			//ft_putstr("\n\n");
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
				if (add_tetrimino(tets->next, canvas_cpy, side_length))
					return (1);
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
	return (1);
}
