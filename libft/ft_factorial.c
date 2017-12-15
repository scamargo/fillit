/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_factorial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 13:38:01 by scamargo          #+#    #+#             */
/*   Updated: 2017/12/08 13:52:04 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_factorial(int nb)
{
	if (nb < 0)
		return (0);
	if (nb == 0 || nb == 1)
		return (1);
	if (nb > 12)
		return (0);
	return (nb * ft_factorial(nb - 1));
}