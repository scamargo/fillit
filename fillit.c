/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:15:26 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/11 15:27:05 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fillit.h"

int		main(int argc, char **argv)
{
	if(argc != 2)
	{
		ft_putstr("usage: ./fillit input_file\n");
		return (1);
	}
	if(!is_valid_input(argv[1]))
	{
		ft_putstr("error\n");
		return (2);
	}
	ft_putstr("input is valid\n");
	ft_putstr(argv[1]);
	ft_putchar('\n');
	return (0);
}
