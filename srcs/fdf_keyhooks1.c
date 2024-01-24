/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keyhooks1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:59:34 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/12 15:59:35 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_get_key_index(int k)
{
	if (k == KEY_ESC)
		return (0);
	else if (k == KEY_ENTER)
		return (1);
	else if (k == KEY_MINUS)
		return (2);
	else if (k == KEY_PLUS)
		return (3);
	else if (k == KEY_LEFT || k == KEY_RIGHT || k == KEY_UP || k == KEY_DOWN)
		return (4);
	else if (k == KEY_R || k == KEY_S || k == KEY_T)
		return (5);
	else if (k == KEY_X || k == KEY_Y || k == KEY_Z)
		return (6);
	else if (k == KEY_0 || k == KEY_1 || k == KEY_2 || k == KEY_3 || k == KEY_4
		|| k == KEY_5 || k == KEY_6 || k == KEY_7 || k == KEY_8 || k == KEY_9)
		return (7);
	else if (k == KEY_I || k == KEY_P)
		return (8);
	return (-1);
}

int	fdf_key_input(int keysym, t_map *map)
{
	int				key_index;

	map->keys->keysym = &keysym;
	key_index = fdf_get_key_index(keysym);
	if (key_index == 0)
		return (map_escape(map));
	else if (key_index == 1)
		return (fdf_hanlde_input_enter(map));
	else if (key_index == 2)
		return (fdf_handle_input_sign(map));
	else if (key_index == 3)
		return (fdf_handle_input_zoom(map));
	else if (key_index == 4)
		return (fdf_handle_input_pan(map));
	else if (key_index == 5)
		return (fdf_handle_input_rst(map));
	else if (key_index == 6)
		return (fdf_handle_input_xyz(map));
	else if (key_index == 7)
		return (fdf_handle_input_nbr(map));
	else if (key_index == 8)
		return (fdf_handle_input_reset(map));
	return (-1);
}

int	fdf_handle_input_reset(t_map *map)
{
	t_keyin	*keys;
	int		keysym;

	keys = map->keys;
	keysym = *(keys->keysym);
	if (keysym == KEY_I)
	{
		arrdbl_free(map->vw->view, 3);
		map->vw->view = arrdbl_init(3, 3, 1);
		view_isometric(map);
		return (map_change(map));
	}
	if (keysym == KEY_P)
	{
		arrdbl_free(map->vw->view, 3);
		map->vw->view = arrdbl_init(3, 3, 1);
		view_plan(map);
		return (map_change(map));
	}
	return (0);
}

int	fdf_handle_input_zoom(t_map *map)
{
	t_keyin	*keys;
	int		keysym;

	keys = (map->keys);
	keysym = *(map->keys->keysym);
	keys->key_tr = 's';
	if (keysym == KEY_MINUS)
		(keys->key_nbr) = 0.9;
	if (keysym == KEY_PLUS)
		(keys->key_nbr) = 1.1;
	return (map_updatevw(map));
}

int	fdf_handle_input_pan(t_map *map)
{
	t_keyin	*keys;
	int		keysym;

	keys = (map->keys);
	keys->key_tr = 't';
	keysym = *(map->keys->keysym);
	if (keysym == KEY_LEFT || keysym == KEY_RIGHT)
		keys->key_ax = 'x';
	else if (keysym == KEY_UP || keysym == KEY_DOWN)
		keys->key_ax = 'y';
	if (keysym == KEY_LEFT)
		(keys->key_nbr) -= 1;
	else if (keysym == KEY_RIGHT)
		(keys->key_nbr) += 1;
	else if (keysym == KEY_UP)
		(keys->key_nbr) -= 1;
	else if (keysym == KEY_DOWN)
		(keys->key_nbr) += 1;
	return (map_updatevw(map));
}
