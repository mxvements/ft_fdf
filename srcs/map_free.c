/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:07:31 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/18 14:07:33 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*map_free(t_map *map)
{
	if (map->map)
		(map->map) = map_free_ptmap(map, map->y_dim);
	if (map->vw)
		map->vw = map_free_vwstruct(map->vw);
	if (map->keys)
		map->keys = map_free_keystruct(map->keys);
	free(map);
	map = NULL;
	return (map);
}

void	*map_free_keystruct(t_keyin *keys)
{
	free(keys);
	keys = NULL;
	return (keys);
}

void	*map_free_vwstruct(t_view *vw)
{
	arrdbl_free(vw->view, 3);
	free(vw);
	vw = NULL;
	return (NULL);
}

void 	*map_free_ptmap(t_map *map, int x)
{
	while (--x >= 0)
	{
		free(map->map[x]);
		map->map[x] = NULL;
	}
	if (map->map)
	{
		free(map->map);
		map->map = NULL;
	}
	if (x < (map->y_dim))
		map_free(map);
	return (map->map);
}
