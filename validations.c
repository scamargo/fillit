/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:32:08 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/19 17:37:13 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "fillit.h"

#define BUFF_SIZE 545

static int is_valid_tetrimino(char str[4][4])
{
	/*Square*/
	/*Line vert*/
	/*Line horiz*/
	/*T*/
	/*T down*/
	/*T right*/
	/*T left*/
	/*J*/
	/*J down*/
	/*J right*/
	/*J left*/
	/*L*/
	/*L down*/
	/*L right*/
	/*L left*/
	/*S*/
	/*S rot*/
	/*Z*/
	/*Z rot*/

	if ((str[0][0] == str[0][1] && str[1][0] == str[1][1]) ||
		(str[0][0] == str[1][0] && str[2][0] == str[3][0]) ||
		(str[0][0] == str[0][1] && str[0][2] == str[0][3]) ||
		(str[0][0] == str[0][1] && str[0][2] == str[1][1]) ||
		(str[0][1] == str[1][0] && str[1][1] == str[1][2]) ||
		(str[1][0] == str[0][1] && str[1][1] == str[2][1]) ||
		(str[0][0] == str[1][0] && str[2][0] == str[1][1]) ||
		(str[0][1] == str[1][1] && str[2][1] == str[2][0]) ||
		(str[0][0] == str[0][1] && str[1][0] == str[2][0]) ||
		(str[0][0] == str[1][0] && str[1][1] == str[1][2]) ||
		(str[0][0] == str[0][1] && str[0][2] == str[1][2]) ||
		(str[0][0] == str[1][0] && str[2][0] == str[2][1]) ||
		(str[0][0] == str[0][1] && str[1][0] == str[2][0]) ||
		(str[0][0] == str[1][0] && str[0][1] == str[0][2]) ||
		(str[1][0] == str[1][1] && str[1][2] == str[0][2]) ||
		(str[0][2] == str[0][1] && str[1][1] == str[1][0]) ||
		(str[0][0] == str[1][0] && str[1][1] == str[2][1]) ||
		(str[0][0] == str[0][1] && str[1][1] == str[1][2]) ||
		(str[2][0] == str[1][0] && str[1][1] == str[0][1]))
			return (1);

	return (0);
}
static void		set_tetrimino_offsets(int *x_off, int *y_off, char *str)
{
	BEGIN_TET_LOOP
	if (str[i] == '#')
	{
		if (*x_off == -1)
			*x_off = x;
		if (*y_off == -1)
			*y_off = y;
	}
	END_TET_LOOP
}

/*
 ** TODO: set tetrimino properties -- leftmost, topmost
*/
static t_tet	*parse_tetrimino(char *str, int tet_count)
{
	t_tet	*tet;
	int		y_offset;
	int		x_offset;
	int		max[2];

	y_offset = -1;
	x_offset = -1;
	max[0] = 0;
	max[1] = 0;
	set_tetrimino_offsets(&x_offset, &y_offset, str);
	if (!(tet = (t_tet*)ft_memalloc(sizeof(t_tet))))
		return (NULL);
	BEGIN_TET_LOOP
	tet->blocks[y][x] = '.';
	if (str[i] == '#')
	{
		tet->blocks[y - y_offset][x - x_offset] = 'A' + tet_count;
		if (x > max[0])
			max[0] = x;
		if (y > max[1])
			max[1] = y;
		tet->width = max[0] - x_offset + 1;
		tet->height = max[1] - y_offset + 1;
	}
	END_TET_LOOP
	tet->used = 0;
	return (tet);
}
	
static int	is_valid_square(char *input, int *i_ptr, t_list **tet_ptr, int count)
{
	int		block_count;
	int		k;
	int		i;
	t_tet	*tet;
	char	str[21];

	block_count = 0;
	k = 0;
	i = *i_ptr;
	while (input[i] && k < 20)
	{
		if (input[i] != '.' && input[i] != '#' && input[i] != '\n')
			return (0);
		if (k > 4 && (k % 5 == 4) && input[i] != '\n')
			return (0);
		if ((k % 5 != 4) && input[i] == '\n')
			return (0);
		if (input[i] == '#')
			block_count++;
		str[k] = input[i];
		i++;
		k++;
	}
	str[k] = '\0';
	if(!(tet = parse_tetrimino(str, count)))
		return (0);
	if (!is_valid_tetrimino(tet->blocks))
		return (0);
	*tet_ptr = ft_lstnew(tet, sizeof(t_tet));
	if (block_count != 4)
		return (0);
	*i_ptr = i;
	return (1);
}

int			is_valid_input(char *input_file, t_list **tets)
{
	int		file_descriptor;
	int		reader;
	char	*buff;
	char	extra_buff[1];
	int		i;
	t_list	*current_tet;
	int		num_of_tetriminos;

	num_of_tetriminos = 0;
	if(!(buff = (char*)ft_memalloc(BUFF_SIZE + 1)))
		return (0);
	file_descriptor = open(input_file, O_RDONLY);
	if (file_descriptor == -1)
		return (0);
	reader = read(file_descriptor, buff, BUFF_SIZE);
	buff[reader] = '\0';
	if (read(file_descriptor, extra_buff, 1))
		return (0);
	i = 0;
	while (1)
	{
		if (!is_valid_square(buff, &i, &current_tet, num_of_tetriminos))
			return (0);
		ft_lstaddtoend(tets, current_tet);
		if (buff[i] == '\0')
			break ;
		if (buff[i++] != '\n')
			return (0);
		num_of_tetriminos++;
	}
	free(buff);
	return (1);
}
