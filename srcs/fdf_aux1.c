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

int	fdf_is_input_arrows(int keysym, t_keyin *keys)
{
	int	nbr;

	nbr = -1;
	keys->key_tr = 'm';
	if (keysym == KEY_left 
		|| keysym == KEY_right 
		|| keysym == KEY_up
		|| keysym == KEY_down)
		nbr = 0;
	return (nbr);
}
 
int	fdf_key_input(int keysym, t_map *map)
{
	static t_keyin	keys;

	fdf_keystruct_init(&keys);
	if (keysym == KEY_ESC)
		return (map_escape(map));
	if (keys.key_tr == 0 
		&& (keysym == KEY_r || keysym == KEY_s || keysym == KEY_t))
		keys.key_tr = fdf_handle_input_rst(keysym);
	if ((keys.key_ax == 0 && (keys.key_tr != 0 || keys.key_tr != 's'))
		&& (keysym == KEY_x || keysym == KEY_y || keysym == KEY_z))
		keys.key_ax = fdf_handle_input_xyz(keysym, &keys);
	if (((keys.key_ax == 0 && keys.key_tr == 's')
		|| (keys.key_ax != 0 && keys.key_tr != 0))
		&& (fdf_is_input_nbr(keysym) != -1))
	{
		keys.key_nbr *= 10;
		keys.key_nbr += fdf_is_input_nbr(keysym);
	}
	if (keys.key_tr == 0 && (keysym == KEY_minus || keysym == KEY_plus))
		return (fdf_hanlde_input_zoom(keysym, &keys, map));
	if (keys.key_tr == 0 && fdf_is_input_arrows(keysym, &keys) != -1)
		return (fdf_handle_input_pan(keysym, &keys, map));
	if (keysym == KEY_ENTER)
		return (map_change(&keys, map));
	return (keysym);
}
