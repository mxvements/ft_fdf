/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:27:32 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/11 23:10:29 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_printview(t_map *map)
{
	int		x;
	int		y;
	t_pt	pt;

	y = 0;
	while (y < (map->y_dim))
	{
		x = 0;
		while (x < (map->x_dim))
		{
			pt = map->map[y][x];
			if ((pt.px_xy[0] < WIDTH && pt.px_xy[1] < HEIGHT)
				&& (pt.px_xy[0] > 0 && pt.px_xy[1] > 0))
				fdf_pxput(&(map->mlx_data), pt.px_xy[0], pt.px_xy[1], pt.color);
			fdf_putlines(map, x, y);
			if (!map)
				return ;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(
		map->mlx_data.mlx,
		map->mlx_data.mlx_win,
		map->mlx_data.img, 0, 0);
}

t_map	*map_mlx(t_map *map)
{
	void	*mlx;

	map->mlx_data.mlx = mlx_init();
	mlx = map->mlx_data.mlx;
	if (!mlx)
		return (NULL);
	map->mlx_data.mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "fdf");
	map->mlx_data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	map->mlx_data.img_addr = mlx_get_data_addr(
			(map->mlx_data).img,
			&(map->mlx_data).bpp,
			&(map->mlx_data).line_len,
			&(map->mlx_data).endian);
	map_printview(map);
	if (!map)
		return (NULL);
	return (map);
}

t_map	*map_pixelptmap(t_map *map)
{
	int				xy[2];
	int				init_pt[2];
	int				center[2];
	t_pt			*pt;

	xy[1] = 0;
	while (xy[1] < (map->y_dim))
	{
		xy[0] = 0;
		while (xy[0] < (map->x_dim))
		{
			pt = &(map->map[xy[1]][xy[0]]);
			center[0] = (map->map[map->y_dim / 2][map->x_dim / 2]).vw_xyz[0];
			center[1] = (map->map[map->y_dim / 2][map->x_dim / 2]).vw_xyz[1];
			init_pt[0] = (WIDTH / 2) - center[0];
			init_pt[1] = (HEIGHT / 2) - center[1];
			pt->px_xy[0] = init_pt[0] + (pt->vw_xyz[0]) + map->vw->move_d_x;
			pt->px_xy[1] = init_pt[1] + (pt->vw_xyz[1]) + map->vw->move_d_y;
			xy[0]++;
		}
		xy[1]++;
	}
	return (map);
}

t_map	*map_viewptmap(t_map *map)
{
	t_view	*vw;
	t_pt	*pt;
	int		x;
	int		y;

	vw = map->vw;
	y = 0;
	while (y < map->y_dim)
	{
		x = 0;
		while (x < map->x_dim)
		{
			pt = &(map->map[y][x]);
			pt_rotate(pt, vw);
			x++;
		}
		y++;
	}
	return (map);
}
