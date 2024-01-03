/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_aux3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 19:50:57 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/03 19:51:06 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	arrdbl_rot_z(t_view *vw)
{
	int				x;
	int				y;
	int				**cpy;
	const double	rot_z[][3] = {\
		{cos(vw->rotate_angle_z), -sin(vw->rotate_angle_z), 0}, \
		{sin(vw->rotate_angle_z), cos(vw->rotate_angle_z), 0}, \
		{0, 0, 1}
	};

	cpy = arrdbl_cpy_3x3(vw->view);
	arrdbl_mult_3x3(cpy, rot_z, vw->view);
	arrdbl_free(cpy, 3);
}

void	arrdbl_rot_y(t_view *vw)
{
	int				x;
	int				y;
	int				**cpy;
	const double	rot_y[][3] = {\
		{cos(vw->rotate_angle_z), 0, sin(vw->rotate_angle_z)}, \
		{0, 1, 0}, \
		{-sin(vw->rotate_angle_z), 0, cos(vw->rotate_angle_z)}
	};

	cpy = arrdbl_cpy_3x3(vw->view);
	arrdbl_mult_3x3(cpy, rot_y, vw->view);
	arrdbl_free(cpy, 3);
}

void	arrdbl_rot_x(t_view *vw)
{
	int				x;
	int				y;
	int				**cpy;
	const double	rot_x[][3] = {\
		{1, 0, 0}, \
		{0, cos(vw->rotate_angle_z), -sin(vw->rotate_angle_z)}, \
		{0, sin(vw->rotate_angle_z), cos(vw->rotate_angle_z)}
	};

	cpy = arrdbl_cpy_3x3(vw->view);
	arrdbl_mult_3x3(cpy, rot_x, vw->view);
	arrdbl_free(cpy, 3);
}
