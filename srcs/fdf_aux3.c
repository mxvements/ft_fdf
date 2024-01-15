/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_aux3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:59:34 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/12 15:59:35 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_handle_input_zoom(t_map *map)
{
	t_keyin	*keys;
	int		keysym;

	keys = &(map->keys);
	keysym = *(map->keys.keysym);
	keys->key_tr = 's';
	if (keysym == KEY_minus)
		(keys->key_nbr) -= 1;
	if (keysym == KEY_plus)
		(keys->key_nbr) += 1;
	return (map_change(map));
}

int	fdf_handle_input_pan(t_map *map)
{
	t_keyin	*keys;
	int		keysym;

	keys = &(map->keys);
	keys->key_tr = 't';
	keysym = *(map->keys.keysym);
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
		(keys->key_nbr) += 1;
	return (map_change(map));
}
