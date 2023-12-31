/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_aux1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:06:19 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/08 23:05:06 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	view_scale(t_view *vw)
{
	int x;
	int y;

	x = 0;
	if (vw->scale_f == 0 || vw->scale_f == 1) //this should not be needed
	{
		vw->scale_f = 1;
		return ;
	}
	while (x < 3)
	{
		y = 0;
		while (y < 3)
		{
			vw->view[x][y] = vw->view[x][y] * vw->scale_f;
			y++;
		}
		x++;
	}
	//vw->scale_f = 1;
}

void	view_translate(t_view *vw)
{
	int	x;
	int	y;

	x = 0;
	if (vw->move_d == 0)
		return ;
	while (x < 3)
	{
		y = 0;
		while (y < 3)
		{
			vw->view[x][y] = vw->view[x][y] + vw->move_d;
			y++;
		}
		x++;
	}
	//vw->move_d = 0;
}

void	view_rotate(t_view *vw)
{
	if (vw->rotate_rads_z != 0)
		view_rot_z(vw);
	//printf("rot_z: \n");
	//arrdbl_print_3x3(vw->view);
	if (vw->rotate_rads_y != 0)
		view_rot_y(vw);
	//printf("rot_y: \n");
	//arrdbl_print_3x3(vw->view);
	if (vw->rotate_rads_x != 0)
		view_rot_x(vw);
	//printf("rot_x: \n");
	//arrdbl_print_3x3(vw->view);
	//vw->rotate_rads_z = 0;
	//vw->rotate_rads_y = 0;
	//vw->rotate_rads_x = 0;
}

void	view_isometric(t_view *vw, int scale)
{
	vw->rotate_rads_z = (M_PI_4);
	vw->rotate_rads_y = 0;
	vw->rotate_rads_x = (M_PI - M_PI_4);
	vw->scale_f = scale;
	vw->move_d = 0;
	view_rotate(vw);
	view_scale(vw);
}
