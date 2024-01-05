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

/* TODO:
** set initview (to isometric)
** set top & side view, reset view at the beginning
** control changes with keys
** change how the pixels are positioned on the canvas
*/
void	map_printview(t_map *map)
{
	int		x;
	int		y;
	int		px_x;
	int		px_y;
	t_view	*vw;

	vw = map->vw;
	x = 0;
	while(x < (map->x_dim))
	{
		y = 0;
		while(y < (map->y_dim))
		{
			px_x = (map->map[x][y].vw_xyz[0]) * vw->scale_factor;
			px_y = (map->map[x][y].vw_xyz[1]) * vw->scale_factor;
			fdf_pixelput(&(map->mlx_data), px_x, px_y, map->map[x][y].color);
			y++;
		}
		x++;
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
	map_printview(map);
	return (map);
}
