/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:20:15 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/11 22:48:19 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*map_evalerror_ptmap(t_map *map, int y)
{
	write(1, ANSICOLOR_RED, 6);
	ft_putstr_fd("Error.\n", 2);
	write(1, ANSICOLOR_RESET, 5);
	return (map_free_ptmap(map, y));
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

t_map	*map_view(t_map *map)
{
	t_view	*vw;

	vw = (t_view *)malloc(sizeof(t_view) * 1);
	if (!vw)
		return (map_free_ptmap(map, map->y_dim));
	map->vw = vw;
	vw->view = arrdbl_init(3, 3, 1);
	view_isometric(map);
	return (map);
}

t_map	*map_ptmap_init(t_map *map)
{
	int	y;

	map->map = (t_pt **)malloc(sizeof(t_pt *) * map->y_dim);
	if (!map->map)
		return (NULL);
	y = 0;
	while (y < map->y_dim)
	{
		map->map[y] = (t_pt *)malloc(sizeof(t_pt) * map->x_dim);
		if (!map->map[y])
			return ((t_map *)map_evalerror_ptmap(map, y));
		y++;
	}
	return (map);
}

t_map	*map_build(char *txt, t_map *map)
{
	map = map_ptmap_init(map);
	if (!map)
		return (NULL);
	map = (t_map *)a_parse(txt, map);
	if (!map)
		return (NULL);
	map = map_view(map);
	if (!map)
		return (NULL);
	map = fdf_keystruct_init(map);
	if (!map)
		return (NULL);
	fdf_show_menu();
	map = map_viewptmap(map);
	map = map_pixelptmap(map);
	map = map_mlx(map);
	if (!map)
		return (NULL);
	return (map);
}
