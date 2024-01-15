/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_aux2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:33:24 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/12 11:33:26 by luciama2         ###   ########.fr       */
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
	const int	nbr = keys->key_nbr;

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

int	fdf_handle_input_rst(t_map *map)
{
	write(1, ANSICOLOR_BLUE, 6);
	if (*(map->keys.keysym) == KEY_r && map->keys.key_tr == 0)
	{
		ft_putstr_fd("********************** rot **********************\n", 1);
		ft_putstr_fd("Press (x) to rotate the X axis\n", 1);
		ft_putstr_fd("Press (y) to rotate the Y axis\n", 1);
		ft_putstr_fd("Press (z) to rotate the Z axis\n", 1);
		map->keys.key_tr = 'r';
	}
	if (*(map->keys.keysym) == KEY_s && map->keys.key_tr == 0)
	{
		ft_putstr_fd("********************** scl **********************\n", 1);
		ft_putstr_fd("Press number to scale on the X axis\n", 1);
		map->keys.key_tr = 's';
	}
	if (*(map->keys.keysym) == KEY_t && map->keys.key_tr == 0)
	{
		ft_putstr_fd("********************** mov **********************\n", 1);
		ft_putstr_fd("Press (x) to move on the X axis\n", 1);
		ft_putstr_fd("Press (y) to move on the Y axis\n", 1);
		ft_putstr_fd("Press (z) to move on the Z axis\n", 1);
		map->keys.key_tr = 'r';
	}
	write(1, ANSICOLOR_RESET, 5);
	return (map->keys.key_tr);
}

int	fdf_handle_input_xyz(t_map *map)
{
	write(1, ANSICOLOR_BLUE, 6);
	if (map->keys.key_tr == 's')
		return (map->keys.key_ax);
	else if (map->keys.key_tr != 0)
	{
		if (*(map->keys.keysym) == KEY_x)
			map->keys.key_ax = 'x';
		else if (*(map->keys.keysym) == KEY_y)
			map->keys.key_ax = 'y';
		else if (*(map->keys.keysym) == KEY_z)
			map->keys.key_ax = 'z';
	}
	if (map->keys.key_tr == 'r')
		ft_putstr_fd("+ Press (nbrs) to ROTATE ", 1);
	if (map->keys.key_tr == 't')
		ft_putstr_fd("+ Press (nbrs) to MOVE ", 1);
	if (map->keys.key_ax == 'x')
		ft_putstr_fd("on the X axis\n", 1);
	else if (map->keys.key_ax == 'y')
		ft_putstr_fd("on the Y axis\n", 1);
	else if (map->keys.key_ax == 'z')
		ft_putstr_fd("on the Z axis\n", 1);
	write(1, ANSICOLOR_RESET, 5);
	return (map->keys.key_ax);
}

int	fdf_handle_input_nbr(t_map *map)
{
	if ((map->keys.key_tr == 's' && map->keys.key_ax == 0) 
		|| (map->keys.key_tr != 0 && map->keys.key_ax != 0))
	{
		if (*(map->keys.keysym) == KEY_0)
			map->keys.key_nbr = (map->keys.key_nbr * 10) + 0;
		if (*(map->keys.keysym) == KEY_1)
			map->keys.key_nbr = (map->keys.key_nbr * 10) + 1;
		if (*(map->keys.keysym) == KEY_2)
			map->keys.key_nbr = (map->keys.key_nbr * 10) + 2;
		if (*(map->keys.keysym) == KEY_3)
			map->keys.key_nbr = (map->keys.key_nbr * 10) + 3;
		if (*(map->keys.keysym) == KEY_4)
			map->keys.key_nbr = (map->keys.key_nbr * 10) + 4;
		if (*(map->keys.keysym) == KEY_5)
			map->keys.key_nbr = (map->keys.key_nbr * 10) + 5;
		if (*(map->keys.keysym) == KEY_6)
			map->keys.key_nbr = (map->keys.key_nbr * 10) + 6;
		if (*(map->keys.keysym) == KEY_7)
			map->keys.key_nbr = (map->keys.key_nbr * 10) + 7;
		if (*(map->keys.keysym) == KEY_8)
			map->keys.key_nbr = (map->keys.key_nbr * 10) + 8;
		if (*(map->keys.keysym) == KEY_9)
			map->keys.key_nbr = (map->keys.key_nbr * 10) + 9;
	}
	return (map->keys.key_nbr);
}
