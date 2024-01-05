/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:27:32 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/05 23:21:10 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*map_view(t_map *map)
{
	t_view	*vw;

	vw = (t_view*)malloc(sizeof(t_view) * 1);
	if (!vw)
		return (map_evalerror(map, map->x_dim));
	map->vw = vw;
	vw->view = arrdbl_init(3, 3, 1);
	view_isometric(vw);
	return (map);
}

t_map	*map_viewptmap(t_map *map)
{
	t_view	*vw;
	t_pt	*pt;
	int		x;
	int		y;

	vw = map->vw;
	x = 0;
	while (x < map->x_dim)
	{
		y = 0;
		while (y < map->y_dim)
		{
			pt = &(map->map[x][y]);
			pt_transform(pt, vw);
			y++;
		}
		x++;
	}
	return (map);
}

t_map	*map_pixelptmap(t_map *map)
{
	int		x;
	int		y;
	t_pt	*pt;

	x = 0;
	while(x < (map->x_dim))
	{
		y = 0;
		while(y < (map->y_dim))
		{
			pt = &(map->map[x][y]);
			pt->px_xy[0] = (WIDTH / 2) + ((pt->vw_xyz[0]));
			pt->px_xy[1] = (HEIGHT / 2) + ((pt->vw_xyz[1]));
			printf("point: {%d, %d}\n", pt->pixel_xy[0], pt->pixel_xy[0]);
			y++;
		}
		x++;
	}
	return (map);
}

void	map_printview(t_map *map)
{
	int		x;
	int		y;
	t_pt	pt;

	x = 0;
	while(x < (map->x_dim))
	{
		y = 0;
		while(y < (map->y_dim))
		{
			pt = map->map[x][y];
			fdf_pixelput(&(map->mlx_data), pt.px_xy[0], pt.px_xy[1], pt.color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(map->mlx_data.mlx, 
							map->mlx_data.mlx_win, 
							map->mlx_data.img, 0, 0);
}

t_map	*map_mlx(t_map *map)
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
