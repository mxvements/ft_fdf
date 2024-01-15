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
	mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
	//TODO: FREE THINGS?
	//exit(EXIT_SUCCESS);
	write(1, ANSICOLOR_RESET, 5);
	return (-1);
}


int	map_change(t_map *map)
{
	t_keyin *keys;

	keys = &(map->keys);
	fdf_show_transformation(keys);
	printf("change map\n");
	printf("key_tra:  %d, key_ax: %d, key_nbr. %d\n", keys->key_tr, keys->key_ax, keys->key_nbr);
	//change map
	//reset mlx
	free(map->mlx_data.img);
	map->mlx_data.img = mlx_new_image(map->mlx_data.mlx, WIDTH, HEIGHT);
	free(map->mlx_data.img_addr);
	map->mlx_data.img_addr = mlx_get_data_addr((map->mlx_data).img,
								&(map->mlx_data).bpp, &(map->mlx_data).line_len,
								&(map->mlx_data).endian);
	//1st change view array
	if (keys->key_tr == 'r')
	{
		if (keys->key_ax == 'x')
			map->vw->rotate_rads_x += keys->key_nbr;
		if (keys->key_ax == 'y')
			map->vw->rotate_rads_y += keys->key_nbr;
		if (keys->key_ax == 'z')
			map->vw->rotate_rads_z += keys->key_nbr;
		view_rotate(map->vw);
	}
	if (keys->key_tr == 's')
	{
		printf("scale: %f\n", map->vw->scale_f);
		map->vw->scale_f += keys->key_nbr;
		printf("scale: %f\n", map->vw->scale_f);
		view_scale(map->vw, map->vw->scale_f);
	}
	if (keys->key_tr == 't')
	{
		if (keys->key_ax == 'x')
			map->vw->move_d_x += keys->key_nbr * 10;
		if (keys->key_ax == 'y')
			map->vw->move_d_y += keys->key_nbr * 10;
	}
	map = map_viewptmap(map); //transform points
	map = map_pixelptmap(map); //get pixel coord
	
	//4th reprint pixels
	map_printview(map);
	//reset data
	fdf_keystruct_reset(keys);
	printf("key_tra:  %d, key_ax: %d, key_nbr. %d\n", keys->key_tr, keys->key_ax, keys->key_nbr);
	return (1);
}
