/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:32:08 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/14 23:55:22 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "fillit.h"

#define BUFF_SIZE 545

static void		set_tetrimino_offsets(int *x_off, int *y_off, char *str)
{
	int y;
	int x;
	int i;
	
	y = 0;
	i = 0;
	*y_off = -1;
	*x_off = -1;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (str[i] == '#')
			{
				if (*x_off == -1)
					*x_off = x;
				if (*y_off == -1)
					*y_off = y;
			}
			x++;
			i++;
		}
		y++;
		i++;
	}
}

// TODO: set blocks in top-left of array
static t_tet	*parse_tetrimino(char *str, int tet_count)
{
	t_tet	*tet;
	int		y;
	int		x;
	int		i;
	int		y_offset;
	int		x_offset;

	// TODO: validate tetrimino
	y_offset = 0;
	x_offset = 0;
	set_tetrimino_offsets(&x_offset, &y_offset, str);
	if (!(tet = (t_tet*)ft_memalloc(sizeof(t_tet))))
		return (NULL);
	i = 0;
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			tet->blocks[y][x] = '.';
			if (str[i] == '#')
				tet->blocks[y - y_offset][x - x_offset] = 'A' + tet_count;
			x++;
			i++;
		}
		y++;
		i++;
	}
	//tet->height = 1;
	//tet->width = 4;
	//tet->leftmost = {0, 0};
	//tet->topmost = {0, 0};
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
	*tet_ptr = ft_lstnew(tet, sizeof(t_tet));
	if (block_count != 4)
		return (0);
	*i_ptr = i;
	return (1);
}

int			is_valid_input(char *input_file, char **buff_ptr, t_list **tets)
{
	int		file_descriptor;
	int		reader;
	char	*buff;
	char	extra_buff[1];
	int		i;
	t_list	*current_tet;
	int		n;

	if(!(*buff_ptr = (char*)ft_memalloc(BUFF_SIZE + 1)))
		return (0);
	buff = *buff_ptr;
	file_descriptor = open(input_file, O_RDONLY);
	if (file_descriptor == -1)
		return (0);
	reader = read(file_descriptor, buff, BUFF_SIZE);
	buff[reader] = '\0';
	if (read(file_descriptor, extra_buff, 1))
		return (0);
	i = 0;
	n = 0;
	while (1)
	{
		if (!is_valid_square(buff, &i, &current_tet, n))
			return (0);
		// TODO: add validated tetrimino to BACK of linked list
		ft_lstadd(tets, current_tet);
		if (buff[i] == '\0')
			break ;
		if (buff[i++] != '\n')
			return (0);
		n++;
	}
	return (1);
}
