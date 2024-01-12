/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_change.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:44:56 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/12 14:44:58 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	map_escape(t_map *map)
{
	t_mlx	*mlx_data;

	mlx_data = &(map->mlx_data);
	write(1, ANSICOLOR_MAGENTA, 6);
	write(1, "(EXC)\n", 6);
	mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
	//TODO: FREE THINGS?
	//exit(EXIT_SUCCESS);
	write(1, ANSICOLOR_RESET, 5);
	return (-1);
}


int	map_change(t_keyin *keys, t_map *map)
{
	fdf_show_transformation(keys);
	printf("change map\n");
	printf("key_tra:  %d, key_ax: %d, key_nbr. %d\n", keys->key_tr, keys->key_ax, keys->key_nbr);
	fdf_keystruct_reset(keys);
	printf("key_tra:  %d, key_ax: %d, key_nbr. %d\n", keys->key_tr, keys->key_ax, keys->key_nbr);
	printf("1st point: %d, %d\n", map->map[0]->px_xy[0], map->map[0]->px_xy[1]);
	return (0);
}