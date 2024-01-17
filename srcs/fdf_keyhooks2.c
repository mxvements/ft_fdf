/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keyhooks2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:33:24 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/12 11:33:26 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_handle_input_rst(t_map *map)
{
	write(1, ANSICOLOR_BLUE, 6);
	if (*(map->keys->keysym) == KEY_r && map->keys->key_tr == 0)
	{
		ft_putstr_fd("********************** rot **********************\n", 1);
		ft_putstr_fd("Press (x) to rotate the X axis\n", 1);
		ft_putstr_fd("Press (y) to rotate the Y axis\n", 1);
		ft_putstr_fd("Press (z) to rotate the Z axis\n", 1);
		map->keys->key_tr = 'r';
	}
	if (*(map->keys->keysym) == KEY_s && map->keys->key_tr == 0)
	{
		ft_putstr_fd("********************** scl **********************\n", 1);
		ft_putstr_fd("Press number to scale on the X axis\n", 1);
		map->keys->key_tr = 's';
	}
	if (*(map->keys->keysym) == KEY_t && map->keys->key_tr == 0)
	{
		ft_putstr_fd("********************** mov **********************\n", 1);
		ft_putstr_fd("Press (x) to move on the X axis\n", 1);
		ft_putstr_fd("Press (y) to move on the Y axis\n", 1);
		ft_putstr_fd("Press (z) to move on the Z axis\n", 1);
		map->keys->key_tr = 't';
	}
	write(1, ANSICOLOR_RESET, 5);
	return (map->keys->key_tr);
}

int	fdf_handle_input_xyz(t_map *map)
{
	write(1, ANSICOLOR_BLUE, 6);
	if (map->keys->key_tr == 's')
		return (map->keys->key_ax);
	else if (map->keys->key_tr != 0)
	{
		if (*(map->keys->keysym) == KEY_x)
			map->keys->key_ax = 'x';
		else if (*(map->keys->keysym) == KEY_y)
			map->keys->key_ax = 'y';
		else if (*(map->keys->keysym) == KEY_z)
			map->keys->key_ax = 'z';
	}
	if (map->keys->key_tr == 'r')
		ft_putstr_fd("+ Press (nbrs) to ROTATE ", 1);
	if (map->keys->key_tr == 't')
		ft_putstr_fd("+ Press (nbrs) to MOVE ", 1);
	if (map->keys->key_ax == 'x')
		ft_putstr_fd("on the X axis\n", 1);
	else if (map->keys->key_ax == 'y')
		ft_putstr_fd("on the Y axis\n", 1);
	else if (map->keys->key_ax == 'z')
		ft_putstr_fd("on the Z axis\n", 1);
	write(1, ANSICOLOR_RESET, 5);
	return (map->keys->key_ax);
}

int	fdf_handle_input_sign(t_map *map)
{
	t_keyin	*keys;

	keys = (map->keys);
	if (keys->key_tr != 0 && keys->key_ax !=0)
	{
		keys->key_sign = -1;
		return (fdf_handle_input_nbr(map));
	}
	return (fdf_handle_input_zoom(map));
}

int	fdf_handle_input_nbr(t_map *map)
{
	if ((map->keys->key_tr == 's' && map->keys->key_ax == 0) 
		|| (map->keys->key_tr != 0 && map->keys->key_ax != 0))
	{
		if (*(map->keys->keysym) == KEY_0)
			map->keys->key_nbr = (map->keys->key_nbr * 10);
		if (*(map->keys->keysym) == KEY_1)
			map->keys->key_nbr = (map->keys->key_nbr * 10) + 1;
		if (*(map->keys->keysym) == KEY_2)
			map->keys->key_nbr = (map->keys->key_nbr * 10) + 2;
		if (*(map->keys->keysym) == KEY_3)
			map->keys->key_nbr = (map->keys->key_nbr * 10) + 3;
		if (*(map->keys->keysym) == KEY_4)
			map->keys->key_nbr = (map->keys->key_nbr * 10) + 4;
		if (*(map->keys->keysym) == KEY_5)
			map->keys->key_nbr = (map->keys->key_nbr * 10) + 5;
		if (*(map->keys->keysym) == KEY_6)
			map->keys->key_nbr = (map->keys->key_nbr * 10) + 6;
		if (*(map->keys->keysym) == KEY_7)
			map->keys->key_nbr = (map->keys->key_nbr * 10) + 7;
		if (*(map->keys->keysym) == KEY_8)
			map->keys->key_nbr = (map->keys->key_nbr * 10) + 8;
		if (*(map->keys->keysym) == KEY_9)
			map->keys->key_nbr = (map->keys->key_nbr * 10) + 9;
	}
	return (map->keys->key_nbr);
}
