/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:15:26 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/21 22:28:43 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

int		main(int argc, char **argv)
{
	t_list	*tets;
	int		num_of_tetriminos;

	num_of_tetriminos = 0;
	tets = NULL;
	if (argc != 2)
	{
		ft_putstr("usage: ./fillit input_file\n");
		return (1);
	}
	if (!is_valid_input(argv[1], &tets, &num_of_tetriminos))
	{
		ft_putstr("error\n");
		return (2);
	}
	if (!find_square(tets, num_of_tetriminos))
	{
		ft_putstr("malloc error\n");
		return (3);
	}
	return (0);
}
