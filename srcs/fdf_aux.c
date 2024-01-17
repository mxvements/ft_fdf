/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:55:41 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/12 00:21:54 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_show_menu(void)
{
	write(1, ANSICOLOR_BLUE, 6);
	ft_putstr_fd("********************** fdf **********************\n", 1);
	ft_putstr_fd("Press (ESC) to close window\n", 1);
	ft_putstr_fd("Press (r) to rotate (WIP)\n", 1);
	ft_putstr_fd("Press (s) to scale (WIP)\n", 1);
	ft_putstr_fd("Press (t) to translate (WIP)\n", 1);
	write(1, ANSICOLOR_RESET, 5);
}

void	fdf_show_transformation(t_keyin *keys)
{
	const int	transf = keys->key_tr;
	const int	axis = keys->key_ax;
	const int	nbr = keys->key_nbr * keys->key_sign;

	write(1, ANSICOLOR_MAGENTA, 6);
	if (transf == 'r')
		ft_putstr_fd("+ ROTATING in ", 1);
	else if (transf == 's')
		ft_putstr_fd("+ SCALING ", 1);
	else if (transf == 't')
		ft_putstr_fd("+ TRASLATING in ", 1);
	if (axis == 'x')
		ft_putstr_fd("axis (X) ", 1);
	else if (axis == 'y')
		ft_putstr_fd("axis (Y) ", 1);
	else if (axis == 'z')
		ft_putstr_fd("axis (Z) ", 1);
	ft_putnbr_fd(nbr, 1);
	ft_putstr_fd("px\n", 1);
	write(1, ANSICOLOR_RESET, 5);
}

static void	fdf_show_rot(t_view *vw)
{
	if (vw->rot_rad_x != 0)
	{
		ft_putstr_fd("+ ROTATING in axis (X) ", 1);
		ft_putnbr_fd(vw->rot_rad_x, 1);
		ft_putstr_fd("px\n", 1);
	}
	if (vw->rot_rad_y != 0)
	{
		ft_putstr_fd("+ ROTATING in axis (Y) ", 1);
		ft_putnbr_fd(vw->rot_rad_y, 1);
		ft_putstr_fd("px\n", 1);
	}
	if (vw->rot_rad_z != 0)
	{
		ft_putstr_fd("+ ROTATING in axis (Z) ", 1);
		ft_putnbr_fd(vw->rot_rad_z, 1);
		ft_putstr_fd("px\n", 1);
	}
}
static void	fdf_show_move(t_view *vw)
{
	if (vw->move_d_x != 0)
	{
		ft_putstr_fd("+ MOVING in axis (X) ", 1);
		ft_putnbr_fd(vw->move_d_x, 1);
		ft_putstr_fd("px\n", 1);
	}
	if (vw->move_d_y != 0)
	{
		ft_putstr_fd("+ MOVING in axis (Y) ", 1);
		ft_putnbr_fd(vw->move_d_y, 1);
		ft_putstr_fd("px\n", 1);
	}
}

void	fdf_show_view(t_view *vw)
{
	write(1, ANSICOLOR_MAGENTA, 6);
	if (vw->rot_rad_x != 0 || vw->rot_rad_y != 0 || vw->rot_rad_z != 0)
		fdf_show_rot(vw);
	if (vw->scale_f != 0)
	{
		ft_putstr_fd("+ SCALING ", 1);
		ft_putnbr_fd(vw->rot_rad_z, 1);
		ft_putstr_fd("px\n", 1);
	}
	if (vw->move_d_x != 0 || vw->move_d_y != 0)
		fdf_show_move(vw);
	write(1, ANSICOLOR_RESET, 5);
}

void	fdf_keystruct_reset(t_keyin *keys)
{
	keys->key_tr = 0;
	keys->key_ax = 0;
	keys->key_nbr = 0;
	keys->key_sign = 1;
	keys->mouse_xy[0] = 0;
	keys->mouse_xy[1] = 0;
	keys->mouse_flag = 0;
}

t_map	*fdf_keystruct_init(t_map *map)
{
	map->keys = (t_keyin *)malloc(sizeof(t_keyin) * 1);
	if (!map->keys)
		return (NULL);
	map->keys->key_tr = 0;
	map->keys->key_ax = 0;
	map->keys->key_nbr = 0;
	map->keys->key_sign = 1;
	map->keys->mouse_xy[0] = 0;
	map->keys->mouse_xy[1] = 0;
	(map->keys->mouse_flag) = 0;
	return (map);
}
