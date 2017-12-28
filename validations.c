/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:32:08 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/27 20:35:03 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "fillit.h"

#define BUFF_SIZE 545
#define A(c) ((c>='A'&&c<='Z')||(c>='a'&&c<='z'))

/*
** Square
** Line vert
** Line horiz
** T
** T down
** T right
** T left
** J
** J down
** J right
** J left
** L
** L down
** L right
** L left
** S
** S rot
** Z
** L left upside-down
** Z
*/

static int		is_valid_tet(char s[4][4])
{
	if ((A(s[0][0]) && A(s[0][1]) && A(s[1][0]) && A(s[1][1])) ||
		(A(s[0][0]) && A(s[1][0]) && A(s[2][0]) && A(s[3][0])) ||
		(A(s[0][0]) && A(s[0][1]) && A(s[0][2]) && A(s[0][3])) ||
		(A(s[0][0]) && A(s[0][1]) && A(s[0][2]) && A(s[1][1])) ||
		(A(s[0][1]) && A(s[1][0]) && A(s[1][1]) && A(s[1][2])) ||
		(A(s[1][0]) && A(s[0][1]) && A(s[1][1]) && A(s[2][1])) ||
		(A(s[0][0]) && A(s[1][0]) && A(s[2][0]) && A(s[1][1])) ||
		(A(s[0][1]) && A(s[1][1]) && A(s[2][1]) && A(s[2][0])) ||
		(A(s[0][0]) && A(s[0][1]) && A(s[1][0]) && A(s[2][0])) ||
		(A(s[0][0]) && A(s[1][0]) && A(s[1][1]) && A(s[1][2])) ||
		(A(s[0][0]) && A(s[0][1]) && A(s[0][2]) && A(s[1][2])) ||
		(A(s[0][0]) && A(s[1][0]) && A(s[2][0]) && A(s[2][1])) ||
		(A(s[0][0]) && A(s[0][1]) && A(s[1][0]) && A(s[2][0])) ||
		(A(s[0][0]) && A(s[1][0]) && A(s[0][1]) && A(s[0][2])) ||
		(A(s[1][0]) && A(s[1][1]) && A(s[1][2]) && A(s[0][2])) ||
		(A(s[0][2]) && A(s[0][1]) && A(s[1][1]) && A(s[1][0])) ||
		(A(s[0][0]) && A(s[1][0]) && A(s[1][1]) && A(s[2][1])) ||
		(A(s[0][0]) && A(s[0][1]) && A(s[1][1]) && A(s[1][2])) ||
		(A(s[0][0]) && A(s[0][1]) && A(s[1][1]) && A(s[2][1])) ||
		(A(s[2][0]) && A(s[1][0]) && A(s[1][1]) && A(s[0][1])))
		return (1);
	return (0);
}

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

static t_tet	*parse_tet(char *str, int tet_count)
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

static int	trim_input(char *in, char *str, int *i_ptr, int *count_ptr)
{
	int		i;
	int		k;

	i = *i_ptr;
	k = 0;
	while (in[i] && k < 20)
	{
		if (in[i] != '.' && in[i] != '#' && in[i] != '\n')
			return (0);
		if (k > 4 && (k % 5 == 4) && in[i] != '\n')
			return (0);
		if ((k % 5 != 4) && in[i] == '\n')
			return (0);
		if (in[i] == '#')
			(*count_ptr)++;
		str[k] = in[i];
		i++;
		k++;
	}
	str[k] = '\0';
	*i_ptr = i;
	return (1);
}

static int	is_valid_sq(char *in, int *i_ptr, t_list **tet_ptr, int count)
{
	int		block_count;
	t_tet	*tet;
	char	new_str[21];

	block_count = 0;
	trim_input(in, new_str, i_ptr, &block_count);
	if (block_count != 4 || !(tet = parse_tet(new_str, count)))
		return (0);
	if (!is_valid_tet(tet->blocks))
		return (0);
	*tet_ptr = ft_lstnew(tet, sizeof(t_tet));
	return (1);
}

char		*read_input(char *input_file)
{
	char	*buff;
	char	extra_buff[1];
	int		reader;
	int		file_descriptor;

	if (!(buff = (char*)ft_memalloc(BUFF_SIZE + 1)))
		return (NULL);
	file_descriptor = open(input_file, O_RDONLY);
	if (file_descriptor == -1)
		return (NULL);
	reader = read(file_descriptor, buff, BUFF_SIZE);
	buff[reader] = '\0';
	if (read(file_descriptor, extra_buff, 1))
		return (NULL);
	return (buff);
}

int			is_valid_input(char *file, t_list **tets, int *num_of_tets)
{
	char	*buff;
	int		i;
	t_list	*current_tet;

	if (!(buff = read_input(file)))
		return (0);
	i = 0;
	while (1)
	{
		if (!is_valid_sq(buff, &i, &current_tet, *num_of_tets))
			return (0);
		ft_lstaddtoend(tets, current_tet);
		(*num_of_tets)++;
		if (buff[i] == '\0')
			break ;
		if (buff[i++] != '\n')
			return (0);
	}
	free(buff);
	return (1);
}
