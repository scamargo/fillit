/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:30:20 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/21 16:41:37 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H

# define FILLIT_H

# include "libft.h"

typedef struct	s_tet
{
	char	blocks[4][4];
	int		height;
	int		width;
	int		leftmost[2];
	int		topmost[2];
	int		used;
}				t_tet;

# define BEGIN_TET_LOOP int y=0;int x=0;int i=0;while(y<4){x=0;while(x<4){
# define END_TET_LOOP x++;i++;}y++;i++;}

int				is_valid_input(char *file_name, t_list **tets, int *count);
int				find_square(t_list *tets, int num_of_tetriminos);

#endif
