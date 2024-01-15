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

void	view_scale(t_view *vw, double scale)
{
	int x;
	int y;
	//me falta calcular la 'antigua escala' para evitar ir multiplicando continuamente

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
			vw->view[x][y] = vw->view[x][y] * scale;
			y++;
		}
		x++;
	}
	//vw->scale_f = 1;
}

void	view_rotate(t_view *vw)
{
	//printf("rot_x: \n");
	//arrdbl_print_3x3(vw->view);
	if (vw->rotate_rads_x != 0)
		view_rot_x(vw);
	//printf("rot_y: \n");
	//arrdbl_print_3x3(vw->view);
	if (vw->rotate_rads_y != 0)
		view_rot_y(vw);
	//printf("rot_z: \n");
	//arrdbl_print_3x3(vw->view);
	if (vw->rotate_rads_z != 0)
		view_rot_z(vw);
	//vw->rotate_rads_z = 0;
	//vw->rotate_rads_y = 0;
	//vw->rotate_rads_x = 0;
}
//where α = arcsin(tan 30°) ≈ 35.264° and β = 45°. A
void	view_isometric(t_map *map)
{
	t_view	*vw;

	vw = map->vw;
	vw->rotate_rads_z = (M_PI_4);
	vw->rotate_rads_y = 0;
	vw->rotate_rads_x = (atan(sqrt(2)));
	vw->scale_f = 1;
	vw->move_d_x = 0;
	vw->move_d_y = 0;
	vw->move_d_z = 0;
	view_rotate(vw);
	view_scale(vw, SCALE);
	view_scale(vw, vw->scale_f);
}
