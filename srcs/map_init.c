/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 14:20:15 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/30 14:20:28 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void 	*map_evalerror(t_map *map)
{
	int	x;

	if (!map)
		return (NULL);
	ft_putstr_fd("Error.\n", 2);
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

t_map	*map_buildptmap(t_map *map, t_dll **ptlst)
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

t_map	*map_init(t_dll **ptlst, char *txt)
{
	t_map		*map;
	const int	ptlst_size = ft_dllsize(*ptlst);

	map = (t_map*)malloc(sizeof(t_map));
	if (!map)
		return ((t_map*)lst_evalerror(ptlst));
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
	//TO DElETE THIS PRINTS
	ft_putnbr_fd(map->x_dim, 1);
	write(1, " - ", 3);
	ft_putnbr_fd(map->y_dim, 1);
	write(1, "\n", 1);
	//Update point map
	map = map_buildptmap(map, ptlst);
	//TODO: update map view to default (isometric projection)
	///GENERATE IMG/WDW and so on..
	ft_dllfree(ptlst);
	free(ptlst);
	return (map);
}
