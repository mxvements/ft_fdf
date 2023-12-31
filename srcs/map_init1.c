/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:20:15 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/31 23:10:40 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void 	*map_evalerror(t_map *map)
{
	int	x;

	write(1, ANSICOLOR_RED, 6);
	ft_putstr_fd("Error.\n", 2);
	write(1, ANSICOLOR_RESET, 5);
	if (!map->map)
	{
		free(map);
		map = NULL;
		return (map);
	}
	x = 0;
	while (x < map->x_dim)
	{
		if (!map->map[x])
			break ;
		free(map->map[x]);
		map->map[x] = NULL;
		x++;
	}
	free(map->map);
	map->map = NULL;
	free(map);
	map = NULL;
	return (NULL);
}

t_dll	*map_getptinfo(t_dll *ptnode, t_map *map, int x, int y)
{
	t_ptcont	*ptcont;

	if (!ptnode)
		return (NULL);
	ptcont = ptnode->content;
	(map->map[x][y]).xyz[0] = x;
	(map->map[x][y]).xyz[1] = y;
	(map->map[x][y]).xyz[2] = ptcont->height;
	(map->map[x][y]).color = ptcont->color;
	ptnode = ptnode->next;
	return (ptnode);
}

t_map	*map_initdptmap(t_map *map, t_dll **ptlst)
{
	int			x;
	int	 		y;
	t_dll		*ptnode;

	ptnode = *ptlst;
	map->map = (t_pt **)malloc(sizeof(t_pt *) * map->x_dim);
	if (!map->map)
		return ((t_map *)lst_evalerror(ptlst));
	x = 0;
	while (x < map->x_dim)
	{
		map->map[x] = (t_pt*)malloc(sizeof(t_pt) * map->y_dim);
		if (!map->map[x])
			return ((t_map *)map_evalerror(map));
		y = 0;
		while (y < map->y_dim)
		{
			ptnode = map_getptinfo(ptnode, map, x, y);
			y++;
		}
		x++;
	}
	if (ptnode)
		return ((t_map *)map_evalerror(map));
	return (map);
}

t_map	*map_initsize(t_dll **ptlst, char *txt, t_map *map)
{
	const int	ptlst_size = ft_dllsize(*ptlst);
	
	map->y_dim = ft_strchr_count(txt, '\n');
	if (map->y_dim == 0 || ptlst_size == 0)
	{
		map->map = NULL;
		map = map_evalerror(map);
		ft_dllfree(ptlst);
		free(ptlst);
		return (NULL);
	}
	map->x_dim = (ptlst_size / map->y_dim);
	return (map);
}

t_map	*map_init(t_dll **ptlst, char *txt)
{
	t_map		*map;
	
	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
		return ((t_map*)lst_evalerror(ptlst));
	map = map_initsize(ptlst, txt, map);
	map = map_initdptmap(map, ptlst);
	map = map_initmlx(map);
	return (map);
}
