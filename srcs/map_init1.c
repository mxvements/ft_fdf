/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:20:15 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/11 22:48:19 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*map_evalerror_ptmap(t_map *map, int x)
{
	write(1, ANSICOLOR_RED, 6);
	ft_putstr_fd("Error.\n", 2);
	write(1, ANSICOLOR_RESET, 5);
	return (map_free_ptmap(map, x));
}

t_dll	*map_getptinfo(t_dll *ptnode, t_map *map, int x, int y)
{
	t_ptcont	*ptcont;

	if (!ptnode)
		return (NULL);
	ptcont = ptnode->content;
	(map->map[y][x]).xyz[0] = x;
	(map->map[y][x]).xyz[1] = y;
	(map->map[y][x]).xyz[2] = ptcont->height / ZSCALE;
	(map->map[y][x]).color = ptcont->color;
	ptnode = ptnode->next;
	return (ptnode);
}

t_map	*map_ptmap(t_map *map, t_dll **ptlst)
{
	int			x;
	int	 		y;
	t_dll		*ptnode;

	ptnode = *ptlst;
	map->map = (t_pt **)malloc(sizeof(t_pt *) * map->y_dim);
	if (!map->map)
		return ((t_map *)lst_evalerror(ptlst));
	y = 0;
	while (y < map->y_dim)
	{
		map->map[y] = (t_pt*)malloc(sizeof(t_pt) * map->x_dim);
		if (!map->map[y])
			return ((t_map *)map_evalerror_ptmap(map, y));
		x = 0;
		while (x < map->x_dim)
		{
			ptnode = map_getptinfo(ptnode, map, x, y);
			x++;
		}
		y++;
	}
	if (ptnode)
		return ((t_map *)map_evalerror_ptmap(map, map->y_dim));
	return (map);
}

t_map	*map_size(t_dll **ptlst, char *txt, t_map *map)
{
	const int	ptlst_size = ft_dllsize(*ptlst);
	
	map->y_dim = ft_strchr_count(txt, '\n');
	if (map->y_dim == 0 || ptlst_size == 0)
	{
		map->map = map_evalerror_ptmap(map, 0);
		return (NULL);
	}
	map->x_dim = (ptlst_size / map->y_dim);
	return (map);
}

void	*map_init(void)
{
	t_map *map;

	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->keys = NULL;
	map->vw = NULL;
	map->map = NULL;
	return ((void *)map);

}

t_map	*fdf_init(t_dll **ptlst, char *txt)
{
	t_map		*map;
	
	map = (t_map*)map_init();
	if (!map)
		return (NULL);
	map = map_size(ptlst, txt, map);
	if (!map)
		return (NULL);
	map = map_ptmap(map, ptlst);
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
	return (map);
}
