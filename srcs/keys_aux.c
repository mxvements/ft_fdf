/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:35:43 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/18 11:36:10 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_keystruct_reset(t_keyin *keys)
{
	keys->key_tr = 0;
	keys->key_ax = 0;
	keys->key_nbr = 0;
	keys->key_sign = 1;
	keys->mouse_xy[0] = 0;
	keys->mouse_xy[1] = 0;
	keys->mouse_flag = 0;
}

t_map	*fdf_keystruct_init(t_map *map)
{
	map->keys = (t_keyin *)malloc(sizeof(t_keyin) * 1);
	if (!map->keys)
		return (NULL);
	map->keys->key_tr = 0;
	map->keys->key_ax = 0;
	map->keys->key_nbr = 0;
	map->keys->key_sign = 1;
	map->keys->mouse_xy[0] = 0;
	map->keys->mouse_xy[1] = 0;
	(map->keys->mouse_flag) = 0;
	return (map);
}
