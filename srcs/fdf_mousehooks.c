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

//int (*f)(int button, int x, int y, void *param)
int	fdf_mousedown_input(int button, int x, int y, t_map *map)
{
	t_keyin	*keys;

	//fdf_keystruct_init((map->keys));
	keys = (map->keys);
	//printf("button: %d\n", button); //TODO: delete
	//printf("map: %p\n", map); //TODO: delete
	if (button == 4 || button == 5)
	{
		keys->key_tr = 's';
		if (button == 4) //4 zoom in
			(keys->key_nbr) = 1.1;
		if (button == 5) //5 zoom out
			(keys->key_nbr) = 0.9;
		return (map_change(map));
	}
	if (button == 2)
	{
		keys->mouse_xy[0] = x;
		keys->mouse_xy[1] = y;
		printf("x:%d y:%d\n", x, y);
		(keys->mouse_flag) = 1;
		printf("mouse flag: %d\n", (map->keys->mouse_flag));
	}
	return (1);
}

int	fdf_mouseup_input(int button, int x, int y, t_map *map)
{
	t_keyin	*keys;
	int		xf;
	int		yf;

	//fdf_keystruct_init((map->keys));
	keys = (map->keys);
	//printf("button: %d\n", button);//TODO: delete
	//printf("x:%d y:%d map: %p\n", x, y, map);//TODO: delete
	printf("mouse flag: %d\n", (map->keys->mouse_flag));
	if ((keys->mouse_flag) == 1 && button == 2)
	{
		printf("mouse flag: %d\n", (map->keys->mouse_flag));
		free(map->mlx_data.img);
		map->mlx_data.img = mlx_new_image(map->mlx_data.mlx, WIDTH, HEIGHT);
		free(map->mlx_data.img_addr);
		map->mlx_data.img_addr = mlx_get_data_addr((map->mlx_data).img,
								&(map->mlx_data).bpp, &(map->mlx_data).line_len,
								&(map->mlx_data).endian);
		xf = x - keys->mouse_xy[0];
		yf = y - keys->mouse_xy[1];
		map->vw->rotate_rads_x += xf / 5;
		map->vw->rotate_rads_y += yf / 5;
		view_rotate(map->vw);
		map = map_viewptmap(map); //transform points
		map = map_pixelptmap(map); //get pixel coord
		map_printview(map);
		fdf_keystruct_reset(keys);
	}
	return (1);
}
