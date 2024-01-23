/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_mousehooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:11:28 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/16 16:11:29 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_mousedown_input(int button, int x, int y, t_map *map)
{
	t_keyin	*keys;

	keys = (map->keys);
	if (button == 4 || button == 5)
	{
		keys->key_tr = 's';
		if (button == 4)
			(keys->key_nbr) = 1.1;
		if (button == 5)
			(keys->key_nbr) = 0.9;
		return (map_updatevw(map));
	}
	if (button == 2 && keys->mouse_flag == 0)
	{
		keys->mouse_xy[0] = x;
		keys->mouse_xy[1] = y;
		(keys->mouse_flag) = 1;
	}
	else if (button == 2 && keys->mouse_flag == 1)
		fdf_keystruct_reset(keys);
	return (0);
}

int	fdf_mousemove_input(int x, int y, t_map *map)
{
	t_keyin	*keys;

	keys = map->keys;
	if (keys->mouse_flag == 0)
		return (1);
	if ((x < WIDTH && y < HEIGHT) && (x > 0 && y > 0))
	{
		map->vw->rot_rad_x = abs((x - keys->mouse_xy[0])) * (M_PI / 18000);
		map->vw->rot_rad_y = abs((y - keys->mouse_xy[1])) * (M_PI / 18000);
		view_rotate(map->vw);
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
	}
	return (1);
}
