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
	map->keys->key_nbr = 1;
	if (!map->keys->mouse_xy[0])
	{
		map->keys->mouse_xy[0] = 0;
		map->keys->mouse_xy[1] = 0;
	}
	if (!map->keys->mouse_flag)
		(map->keys->mouse_flag) = 0;
	return (map);
}

//int (*f)(int keycode, void *param)
int	fdf_key_input(int keysym, t_map *map)
{
	int				key_index;

	//fdf_keystruct_init(map);
	map->keys->keysym = &keysym;
	key_index = fdf_get_key_index(keysym);
	if (key_index == 0) //esc
		return (map_escape(map));
	else if (key_index == 1) //enter keypad
		return (map_change(map));
	else if (key_index == 2) //- in keypad, sign or zoom
		return (fdf_handle_input_sign(map));
	else if (key_index == 3) //+- in keypad 
		return (fdf_handle_input_zoom(map));
	else if (key_index == 4) //arrowpad 
		return (fdf_handle_input_pan(map));
	else if (key_index == 5) //rst
		return (fdf_handle_input_rst(map));
	else if (key_index == 6) //xyz
		return (fdf_handle_input_xyz(map));
	else if (key_index == 7) //nbrs
		return (fdf_handle_input_nbr(map));
	else
		return (-1);
}

int	fdf_handle_input_zoom(t_map *map)
{
	t_keyin	*keys;
	int		keysym;

	keys = (map->keys);
	keysym = *(map->keys->keysym);
	keys->key_tr = 's';
	if (keysym == KEY_minus)
		(keys->key_nbr) = 0.9;
	if (keysym == KEY_plus)
		(keys->key_nbr) = 1.1;
	return (map_change(map));
}

int	fdf_handle_input_pan(t_map *map)
{
	t_keyin	*keys;
	int		keysym;

	keys = (map->keys);
	keys->key_tr = 't';
	keysym = *(map->keys->keysym);
	if (keysym == KEY_left || keysym == KEY_right)
		keys->key_ax = 'x'; //For default Plane (XY)
	else if (keysym == KEY_up || keysym == KEY_down)
		keys->key_ax = 'y'; //For default Plane (XY)
	if (keysym == KEY_left)
		(keys->key_nbr) -= 1;
	else if (keysym == KEY_right)
		(keys->key_nbr) += 1;
	else if (keysym == KEY_up)
		(keys->key_nbr) -= 1;
	else if (keysym == KEY_down)
		(keys->key_nbr)+= 1;
	return (map_change(map));
}
