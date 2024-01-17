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

int	fdf_get_key_index(int k)
{
	if (k == KEY_ESC)
		return (0);
	else if (k == KEY_ENTER)
		return (1);
	else if (k == KEY_minus)
		return (2);
	else if (k == KEY_plus)
		return (3);
	else if (k == KEY_left || k == KEY_right || k == KEY_up || k == KEY_down)
		return (4);
	else if (k == KEY_r || k == KEY_s || k == KEY_t)
		return (5);
	else if (k == KEY_x || k == KEY_y || k == KEY_z)
		return (6);
	else if (k == KEY_0 || k == KEY_1 || k == KEY_2 || k == KEY_3 || k == KEY_4
		|| k == KEY_5 || k == KEY_6 || k == KEY_7 || k == KEY_8 || k == KEY_9)
		return (7);
	else if (k == KEY_i || k == KEY_p)
		return (8);
	/*else if(k == KEY_u)
		return (9);*/
	return (-1);
}

//int (*f)(int keycode, void *param)
int	fdf_key_input(int keysym, t_map *map)
{
	int				key_index;

	map->keys->keysym = &keysym;
	key_index = fdf_get_key_index(keysym);
	if (key_index == 0) //esc
		return (map_escape(map));
	else if (key_index == 1)//enter keypad
		return (map_updatevw(map));
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
	/*else if (key_index == 8)
		return (fdf_handle_input_reset(map));*/
	else
		return (-1);
}

/*int	fdf_handle_input_reset(t_map *map)
{
	t_keyin	*keys;
	int		keysym;

	keys = map->keys;
	keysym = keys->keysym;
	if (keysym == KEY_i)
	{
		keys->key_ax = 'z'
	}
	if (keysym == KEY_p)
		return ()
}*/

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
	return (map_updatevw(map));
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
	return (map_updatevw(map));
}
