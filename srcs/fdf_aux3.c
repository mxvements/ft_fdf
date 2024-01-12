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

int	fdf_hanlde_input_zoom(int keysym, t_keyin *keys, t_map *map)
{
	keys->key_tr = 's';
	if (keysym == KEY_minus)
		(keys->key_nbr)--;
	if (keysym == KEY_plus)
		(keys->key_nbr)++;
	return (map_change(keys, map));
}

int	fdf_handle_input_pan(int keysym, t_keyin *keys, t_map *map)
{
	if (keysym == KEY_left || keysym == KEY_right)
		keys->key_ax = 'x'; //For default Plane (XY)
	else if (keysym == KEY_up || keysym == KEY_down)
		keys->key_ax = 'y'; //For default Plane (XY)
	if (keysym == KEY_left)
		(keys->key_nbr)--;
	else if (keysym == KEY_right)
		(keys->key_nbr)++;
	else if (keysym == KEY_up)
		(keys->key_nbr)++;
	else if (keysym == KEY_down)
		(keys->key_nbr)--;
	return (map_change(keys, map));
}
