/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:30:20 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/14 23:11:48 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H

# define FILLIT_H

typedef struct s_tet
{
	char	blocks[4][4];
	int		height;
	int		width;
	int		leftmost[2];
	int		topmost[2];
	int		used;
}				t_tet;

int	is_valid_input(char *file_name, char **buff_ptr, t_list **tets);
int	find_square(char *input);

#endif
