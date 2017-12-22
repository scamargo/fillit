/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 22:09:23 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/21 22:27:08 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

static void	print_square(char **canvas, int len)
{
	int y;
	int x;

	y = 0;
	while (y < len)
	{
		x = 0;
		while (x < len)
		{
			ft_putchar(canvas[y][x]);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
}

static char	**init_canvas(int len)
{
	char	**canvas;
	int		y;
	int		x;

	if (!(canvas = ft_init_chartable(len, len)))
		return (NULL);
	BEGIN_TABLE_LOOP
	canvas[y][x] = '.';
	END_TABLE_LOOP
	return (canvas);
}

static int	set_tet(t_tet *tet, char **canvas, int side_length, int start[2])
{
	int x;
	int r;
	int c;

	if ((side_length - start[1]) < tet->height ||
		(side_length - start[0]) < tet->width)
		return (0);
	r = 0;
	while (r < tet->height)
	{
		c = 0;
		x = start[0];
		while (c < tet->width)
		{
			if (canvas[start[1]][x] != '.' && tet->blocks[r][c] != '.')
				return (0);
			if (tet->blocks[r][c] != '.')
				canvas[start[1]][x] = tet->blocks[r][c];
			x++;
			c++;
		}
		start[1]++;
		r++;
	}
	return (1);
}

static int	add_tetrimino(t_list *tets, char **canvas, int len)
{
	char	**canvas_cpy;
	int		y;
	int		x;
	int		start[2];

	if (((t_tet*)tets->content)->width > len || ((t_tet*)tets->content)->height > len)
		return (0);
	if (!(canvas_cpy = ft_init_chartable(len, len)))
		return (0);
	BEGIN_TABLE_LOOP
	start[0] = x;
	start[1] = y;
	ft_memmove(canvas_cpy[0], canvas[0], len * len);
	if (set_tet((t_tet*)tets->content, canvas_cpy, len, start))
	{
		if (!tets->next)
		{
			print_square(canvas_cpy, len);
			ft_destroy_chartable(canvas_cpy);
			return (1);
		}
		if (add_tetrimino(tets->next, canvas_cpy, len))
		{
			ft_destroy_chartable(canvas_cpy);
			return (1);
		}
	}
	END_TABLE_LOOP
	ft_destroy_chartable(canvas_cpy);
	return (0);
}

int			find_square(t_list *tets, int number_of_tetriminos)
{
	int		side_length;
	char	**canvas;
	int total_tetriminos;

	side_length = 1;
	total_tetriminos = number_of_tetriminos * 4;
	while (side_length * side_length < total_tetriminos)
		side_length++;
	if (!(canvas = init_canvas(side_length)))
		return (0);
	while (!add_tetrimino(tets, canvas, side_length))
	{
		ft_destroy_chartable(canvas);
		if (!(canvas = init_canvas(++side_length)))
			return (0);
	}
	return (1);
}
