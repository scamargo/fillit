/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 22:54:55 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/27 17:05:50 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_square(char **canvas, int len)
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

char	**init_canvas(int len)
{
	char	**canvas;
	int		y;
	int		x;

	if (!(canvas = ft_init_chartable(len, len)))
		return (NULL);
	y = 0;
	while (y < len)
	{
		x = 0;
		while (x < len)
		{
			canvas[y][x] = '.';
			x++;
		}
		y++;
	}
	return (canvas);
}
