/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 13:23:18 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/29 14:22:54 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

static void		set_tetrimino_offsets(t_tet *tet, char *str, int i)
{
	int pos[2];
	int min_pos[2];

	pos[0] = 0;
	pos[1] = 0;
	min_pos[0] = 5;
	min_pos[1] = 5;
	while (pos[1] < 4)
	{
		pos[0] = 0;
		while (pos[0] < 4)
		{
			if (str[i] == '#')
			{
				min_pos[0] = (pos[0] < min_pos[0]) ? pos[0] : min_pos[0];
				min_pos[1] = (pos[1] < min_pos[1]) ? pos[1] : min_pos[1];
				tet->x_offset = min_pos[0];
				tet->y_offset = min_pos[1];
			}
			pos[0]++;
			i++;
		}
		pos[1]++;
		i++;
	}
}

static void		set_tet_block(t_tet *tet, int max[2], int tet_count, int pos[2])
{
	int y_offset;
	int x_offset;
	int y;
	int x;

	y = pos[1];
	x = pos[0];
	y_offset = tet->y_offset;
	x_offset = tet->x_offset;
	tet->blocks[y - y_offset][x - x_offset] = 'A' + tet_count;
	max[0] = (x > max[0]) ? x : max[0];
	max[1] = (y > max[1]) ? y : max[1];
	tet->width = max[0] - x_offset + 1;
	tet->height = max[1] - y_offset + 1;
}

static void		set_tet(char *str, t_tet *tet, int max[2], int tet_count)
{
	int		pos[2];
	int		i;

	pos[1] = 0;
	i = 0;
	while (pos[1] < 4)
	{
		pos[0] = 0;
		while (pos[0] < 4)
		{
			tet->blocks[pos[1]][pos[0]] = '.';
			if (str[i] == '#')
				set_tet_block(tet, max, tet_count, pos);
			pos[0]++;
			i++;
		}
		pos[1]++;
		i++;
	}
}

t_tet			*parse_tet(char *str, int tet_count)
{
	t_tet	*tet;
	int		max[2];

	if (!(tet = (t_tet*)ft_memalloc(sizeof(t_tet))))
		return (NULL);
	tet->x_offset = 0;
	tet->y_offset = 0;
	max[0] = 0;
	max[1] = 0;
	set_tetrimino_offsets(tet, str, 0);
	set_tet(str, tet, max, tet_count);
	return (tet);
}
