/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:27:32 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/11 23:10:29 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*map_view(t_map *map)
{
	t_view	*vw;
	//int		scale;

	vw = (t_view*)malloc(sizeof(t_view) * 1);
	if (!vw)
		return (map_evalerror_pt(map, map->y_dim));
	map->vw = vw;
	vw->view = arrdbl_init(3, 3, 1);
	//scale = ((WIDTH * 0.4) / (map->x_dim)); //SCALE OF DRAWING
	//printf("scale in map_view: %d\n", SCALE);
	view_isometric(map);
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

t_map	*map_pixelptmap(t_map *map)
{
	int				x;
	int				y;
	t_pt			*pt;
	const double	f = (map->vw)->scale_f;

	y = 0;
	while(y < (map->y_dim))
	{
		x = 0;
		while(x < (map->x_dim))
		{
			pt = &(map->map[y][x]);
			pt->px_xy[0] = (WIDTH / 2) - ((map->x_dim * f) / 8) + ((pt->vw_xyz[0])); //TODO: fix position
			pt->px_xy[1] = (HEIGHT / 2) - ((map->y_dim * f) / 3) + ((pt->vw_xyz[1]));
			//printf("point: {%d, %d}\n", pt->px_xy[0], pt->px_xy[1]);
			pt->px_xy[0] += map->vw->move_d_x;
			pt->px_xy[1] += map->vw->move_d_y;
			x++;
		}
		y++;
	}
	return (map);
}

void	map_printview(t_map *map)
{
	int		x;
	int		y;
	t_pt	pt;

	y = 0;
	while(y < (map->y_dim))
	{
		x = 0;
		while(x < (map->x_dim))
		{
			pt = map->map[y][x];
			if (pt.px_xy[0] < WIDTH && pt.px_xy[1] < HEIGHT)
				fdf_pixelput(&(map->mlx_data), pt.px_xy[0], pt.px_xy[1], pt.color);
			fdf_putlines(map, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->mlx_data.mlx, map->mlx_data.mlx_win, 
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
	map->mlx_data.img_addr = mlx_get_data_addr((map->mlx_data).img,
								&(map->mlx_data).bpp, &(map->mlx_data).line_len,
								&(map->mlx_data).endian);
	map_printview(map);
	return (map);
}
