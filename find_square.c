/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 22:09:23 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/21 23:32:50 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft.h"

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

static int	solution_found(t_list *tets, char **canvas, int len, int start[1])
{
	if (set_tet((t_tet*)tets->content, canvas, len, start))
	{
		if (!tets->next)
		{
			print_square(canvas, len);
			ft_destroy_chartable(canvas);
			return (1);
		}
		if (add_tetrimino(tets->next, canvas, len))
		{
			ft_destroy_chartable(canvas);
			return (1);
		}
	}
	return (0);
}

int			add_tetrimino(t_list *ts, char **canvas, int l)
{
	char	**canvas_cpy;
	int		y;
	int		x;
	int		start[2];

	if (!(canvas_cpy = ft_init_chartable(l, l)))
		return (0);
	y = 0;
	while (y < l)
	{
		x = 0;
		while (x < l)
		{
			start[0] = x;
			start[1] = y;
			ft_memmove(canvas_cpy[0], canvas[0], l * l);
			if (solution_found(ts, canvas_cpy, l, start))
				return (1);
			x++;
		}
		y++;
	}
	ft_destroy_chartable(canvas_cpy);
	return (0);
}

int			find_square(t_list *tets, int number_of_tetriminos)
{
	int		side_length;
	char	**canvas;
	int		total_tetriminos;

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
