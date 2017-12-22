/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 12:30:20 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/21 23:26:38 by scamargo         ###   ########.fr       */
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
}				t_tet;

# define BEGIN_TET_LOOP int y=0;int x=0;int i=0;while(y<4){x=0;while(x<4){
# define END_TET_LOOP x++;i++;}y++;i++;}
# define BEGIN_TABLE_LOOP y=0;while(y<len){x=0;while(x<len){
# define END_TABLE_LOOP x++;}y++;}

int				is_valid_input(char *file_name, t_list **tets, int *count);
int				find_square(t_list *tets, int num_of_tetriminos);
void			print_square(char **canvas, int len);
char			**init_canvas(int len);
int				add_tetrimino(t_list *ts, char **canvas, int l);

#endif
