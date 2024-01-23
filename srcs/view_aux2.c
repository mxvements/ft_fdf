/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_aux3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:50:57 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/03 19:51:06 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	view_rot_z(t_view *vw)
{
	double	**cpy;
	double	**rot_z;

	rot_z = arrdbl_init(3, 3, 1);
	rot_z[0][0] = cos(vw->rot_rad_z);
	rot_z[0][1] = -sin(vw->rot_rad_z);
	rot_z[0][2] = 0;
	rot_z[1][0] = sin(vw->rot_rad_z);
	rot_z[1][1] = cos(vw->rot_rad_z);
	rot_z[1][2] = 0;
	rot_z[2][0] = 0;
	rot_z[2][1] = 0;
	rot_z[2][2] = 1;
	cpy = arrdbl_cpy_3x3(vw->view);
	arrdbl_mult_3x3(cpy, rot_z, vw->view);
	arrdbl_free(cpy, 3);
	arrdbl_free(rot_z, 3);
}

void	view_rot_y(t_view *vw)
{
	double	**cpy;
	double	**rot_y;

	rot_y = arrdbl_init(3, 3, 1);
	rot_y[0][0] = cos(vw->rot_rad_y);
	rot_y[0][1] = 0;
	rot_y[0][2] = sin(vw->rot_rad_y);
	rot_y[1][0] = 0;
	rot_y[1][1] = 1;
	rot_y[1][2] = 0;
	rot_y[2][0] = -sin(vw->rot_rad_y);
	rot_y[2][1] = 0;
	rot_y[2][2] = cos(vw->rot_rad_y);
	cpy = arrdbl_cpy_3x3(vw->view);
	arrdbl_mult_3x3(cpy, rot_y, vw->view);
	arrdbl_free(cpy, 3);
	arrdbl_free(rot_y, 3);
}

void	view_rot_x(t_view *vw)
{
	double	**cpy;
	double	**rot_x;

	rot_x = arrdbl_init(3, 3, 1);
	rot_x[0][0] = 1;
	rot_x[0][1] = 0;
	rot_x[0][2] = 0;
	rot_x[1][0] = 0;
	rot_x[1][1] = cos(vw->rot_rad_x);
	rot_x[1][2] = -sin(vw->rot_rad_x);
	rot_x[2][0] = 0;
	rot_x[2][1] = sin(vw->rot_rad_x);
	rot_x[2][2] = cos(vw->rot_rad_x);
	cpy = arrdbl_cpy_3x3(vw->view);
	arrdbl_mult_3x3(cpy, rot_x, vw->view);
	arrdbl_free(cpy, 3);
	arrdbl_free(rot_x, 3);
}
