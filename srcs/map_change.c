/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:44:56 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/12 14:44:58 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	map_escape(t_map *map)
{
	t_mlx	*mlx_data;

	mlx_data = &(map->mlx_data);
	write(1, ANSICOLOR_MAGENTA, 6);
	write(1, "(EXC)\n", 6);
	write(1, ANSICOLOR_RESET, 5);
	mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
	free(map->mlx_data.img);
	free(map->mlx_data.img_addr);
	free((map->mlx_data).mlx);
	exit(EXIT_SUCCESS);
	return (-1);
}

int	map_updatevw(t_map *map)
{
	const t_keyin	*keys = (map->keys);

	if (keys->key_tr == 'r')
	{
		if (keys->key_ax == 'x')
			map->vw->rot_rad_x = keys->key_nbr * keys->key_sign * (M_PI / 180);
		if (keys->key_ax == 'y')
			map->vw->rot_rad_y = keys->key_nbr * keys->key_sign * (M_PI / 180);
		if (keys->key_ax == 'z')
			map->vw->rot_rad_z = keys->key_nbr * keys->key_sign * (M_PI / 180);
	}
	if (keys->key_tr == 's')
		map->vw->scale_f = keys->key_nbr * keys->key_sign;
	if (keys->key_tr == 't')
	{
		if (keys->key_ax == 'x')
			map->vw->move_d_x += keys->key_nbr * 10 * keys->key_sign;
		if (keys->key_ax == 'y')
			map->vw->move_d_y += keys->key_nbr * 10 * keys->key_sign;
	}
	view_rotate(map->vw);
	view_scale(map->vw);
	fdf_show_transformation(map->keys);
	return (map_change(map));
}

int	map_change(t_map *map)
{
	t_keyin	*keys;

	keys = (map->keys);
	free(map->mlx_data.img);
	map->mlx_data.img = mlx_new_image(map->mlx_data.mlx, WIDTH, HEIGHT);
	free(map->mlx_data.img_addr);
	map->mlx_data.img_addr = mlx_get_data_addr(
			(map->mlx_data).img,
			&(map->mlx_data).bpp,
			&(map->mlx_data).line_len,
			&(map->mlx_data).endian);
	map = map_viewptmap(map);
	map = map_pixelptmap(map);
	map_printview(map);
	fdf_keystruct_reset(keys);
	return (1);
}
