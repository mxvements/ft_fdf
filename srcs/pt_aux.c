/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pt_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 09:39:12 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/31 19:21:16 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pt_print(t_pt **ptarr, int xdim, int ydim) //need to change this funct
{
	int		x;
	int		y;
	t_pt 	pt;

	x = 0;
	while (x < xdim)
	{
		y = 0;
		while (y < ydim)
		{
			pt = ptarr[x][y];
			ft_putstr_fd("{x,y,x}: {", 1);
			ft_putnbr_fd(pt.xyz[0], 1);
			write(1, ", ", 1);
			ft_putnbr_fd(pt.xyz[1], 1);
			write(1, ", ", 1);
			ft_putnbr_fd(pt.xyz[2], 1);
			ft_putstr_fd("}, color: ", 1);
			ft_putnbr_fd(pt.color, 1);
			write(1, "\n", 1);
			y++;
		}
		x++;
	}
}
