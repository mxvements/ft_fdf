/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:27:32 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/08 20:36:12 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*map_view(t_map *map)
{
	t_view	*vw;
	int		scale;

	vw = (t_view*)malloc(sizeof(t_view) * 1);
	if (!vw)
		return (map_evalerror(map, map->y_dim));
	map->vw = vw;
	vw->view = arrdbl_init(3, 3, 1);
	scale = ((WIDTH * 0.4) / (map->x_dim));
	view_isometric(vw, scale);
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
			pt_transform(pt, vw);
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
	mlx_put_image_to_window(map->mlx_data.mlx, 
							map->mlx_data.mlx_win, 
							map->mlx_data.img, 0, 0);
}

int	map_key_input_wrapper(t_map *map)
{
	int n_tr;
	int n_val;
	int n_ax;
	int	key_in;
	//int	key_out;

	key_in = mlx_key_hook(map->mlx_data.mlx_win, fdf_key_input, &map->mlx_data);
	if (key_in == -1) //return from ESC
		return (-1);
	if (ft_strchr("rst", key_in) != 0)
	{
		n_tr = key_in;
		n_ax = 0;
		printf("n_tr: %d\n", n_tr);
	}
	if (ft_strchr("xyz", key_in) != 0)
		n_val = key_in;
	if (ft_strchr("0123456789", key_in) != 0)
	{
		n_ax *= 10;
		n_ax += key_in;
		printf("n_ax: %d\n", n_ax);
	}
	if (key_in == KEY_F1 && (n_tr != 0 && n_val != 0 && n_ax != 0))
	{
		printf("TODO: redo map / n_tr: %d, n_val: %d, n_ax: %d\n", n_tr, n_val, n_ax);
	}
	return (-1);
}

t_map	*map_mlx(t_map *map)
{
	void	*mlx;
	void	*mlx_win;
	int		key_in;
	
	map->mlx_data.mlx = mlx_init();
	mlx = map->mlx_data.mlx;
	if (!mlx)
		return (NULL);
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "fdf");
	map->mlx_data.mlx_win = mlx_win;
	fdf_show_menu();
	map->mlx_data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	map->mlx_data.img_addr = mlx_get_data_addr(
								(map->mlx_data).img,
								&(map->mlx_data).bpp,
								&(map->mlx_data).line_len,
								&(map->mlx_data).endian);
	map_printview(map);

	//handle output from keyboard
	/*key_input = mlx_key_hook(mlx_win, fdf_key_input, &map->mlx_data);
	if (key_input == -1) //return from ESC
		return (NULL);*/
	key_in = map_key_input_wrapper(map);
	return (map);
}
