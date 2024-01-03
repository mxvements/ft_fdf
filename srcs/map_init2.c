/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:27:32 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/02 10:27:35 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_printtop(t_map *map)
{
	int x;
	int y;
	int offset;
	t_pt	pt;

	//map->offset_pixel = 32;
	offset = 32; //SCALE
	x = 0;
	while(x < (map->x_dim * 32))
	{
		y = 0;
		while(y < (map->y_dim * 32))
		{
			pt = map->map[x/32][y/32];
			fdf_pixelput(&(map->mlx_data), pt.xyz[1] * 32, pt.xyz[2] * 32, pt.color);
			y += 32;
		}
		x += 32;
	}
	mlx_put_image_to_window(map->mlx_data.mlx, 
							map->mlx_data.mlx_win, 
							map->mlx_data.img, 10, 10);
}

t_map	*map_initmlx(t_map *map)
{	
	void	*mlx;
	void	*mlx_win;
	int		key_input;
	
	map->mlx_data.mlx = mlx_init();
	mlx = map->mlx_data.mlx;
	if (!mlx)
		return (NULL);
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "fdf");
	map->mlx_data.mlx_win = mlx_win;
	fdf_show_menu();
	key_input = mlx_key_hook(mlx_win, fdf_handle_input, &map->mlx_data);
	if (key_input == 1)
		return (NULL);
	//¿IMG SIZE?
	map->mlx_data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	map->mlx_data.img_addr = mlx_get_data_addr(
								(map->mlx_data).img,
								&(map->mlx_data).bpp,
								&(map->mlx_data).line_len,
								&(map->mlx_data).endian);
	map_printtop(map);
	return (map);
}
