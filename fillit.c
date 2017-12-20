/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:15:26 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/19 17:26:40 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

// FOR TESTING PURPPOSES
/*void	print_tets(t_list *node)
{
	t_tet	*tet;
	int		y;
	int		x;

	y = 0;
	tet = (t_tet*)node->content;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			ft_putchar(tet->blocks[y][x]);
			x++;
		}
		ft_putchar('\n');
		y++;
	}
	ft_putchar('\n');
}*/

int		main(int argc, char **argv)
{
	t_list	*tets;

	tets = NULL;
	if (argc != 2)
	{
		ft_putstr("usage: ./fillit input_file\n");
		return (1);
	}
	if (!is_valid_input(argv[1], &tets))
	{
		ft_putstr("error\n");
		return (2);
	}
	//ft_lstiter(tets, print_tets);
	if (!find_square(tets))
	{
		ft_putstr("malloc error\n");
		return (3);
	}
	return (0);
}
