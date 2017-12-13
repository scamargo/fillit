/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:32:08 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/12 22:44:05 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "fillit.h"

#define BUFF_SIZE 545

static int	is_valid_square(char *input, int *i_ptr)
{
	int block_count;
	int k;
	int i;

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
		i++;
		k++;
	}
	// TODO: call is_valid_tetrimino
	if (block_count != 4)
		return (0);
	*i_ptr = i;
	return (1);
}

int			is_valid_input(char *input_file, char **buff_ptr)
{
	int		file_descriptor;
	int		reader;
	char	*buff;
	char	extra_buff[1];
	int		i;

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
	while (1)
	{
		if (!is_valid_square(buff, &i))
			return (0);
		if (buff[i] == '\0')
			break ;
		if (buff[i++] != '\n')
			return (0);
	}
	return (1);
}
