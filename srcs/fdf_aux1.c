/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_aux1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:55:41 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/12 00:21:54 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_keystruct_reset(t_keyin *keys)
{
	keys->key_tr = 0;
	keys->key_ax = 0;
	keys->key_nbr = 0;
}

void	fdf_keystruct_init(t_keyin *keys)
{
	if (!keys->key_tr)
		keys->key_tr = 0;
	if (!keys->key_ax)
		keys->key_ax = 0;
	if (!keys->key_nbr)
		keys->key_nbr = 0;
}

int	fdf_get_key_index(int k)
{
	if (k == KEY_ESC)
		return (0);
	else if (k == KEY_ENTER)
		return (1);
	else if (k == KEY_minus || k == KEY_plus)
		return (2);
	else if (k == KEY_left || k == KEY_right || k == KEY_up || k == KEY_down)
		return (3);
	else if (k == KEY_r || k == KEY_s || k == KEY_t)
		return (4);
	else if (k == KEY_x || k == KEY_y || k == KEY_z)
		return (5);
	else if (k == KEY_0 || k == KEY_1 || k == KEY_2 || k == KEY_3 || k == KEY_4
		|| k == KEY_5 || k == KEY_6 || k == KEY_7 || k == KEY_8 || k == KEY_9)
		return (6);
	return (-1);
}

int	fdf_key_input(int keysym, t_map *map)
{
	int				key_index;

	fdf_keystruct_init(&(map->keys));
	map->keys.keysym = &keysym;
	key_index = fdf_get_key_index(keysym);
	if (key_index == 0) //esc
		return (map_escape(map));
	else if (key_index == 1) //enter keypad
		return (map_change(map));
	else if (key_index == 2) //+- in keypad
		return (fdf_handle_input_zoom(map));
	else if (key_index == 3) //arrowpad
		return (fdf_handle_input_pan(map));
	else if (key_index == 4) //rst
		return (fdf_handle_input_rst(map));
	else if (key_index == 5) //xyz
		return (fdf_handle_input_xyz(map));
	else if (key_index == 6) //nbrs
		return (fdf_handle_input_nbr(map));
	else
		return (-1);
}
