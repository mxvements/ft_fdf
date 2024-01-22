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

/*t_dll	*map_getptinfo(t_dll *ptnode, t_map *map, int x, int y) //ESTO CAMBIA, DELETE
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

t_map	*map_ptmap(t_map *map, t_dll **ptlst) //ESTO CAMBIA
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
		while (x < map->x_dim) //este while no sería necesaria, el ptmap ya está iniciado
		{
			ptnode = map_getptinfo(ptnode, map, x, y);
			x++;
		}
		y++;
	}
	if (ptnode)
		return ((t_map *)map_evalerror_ptmap(map, map->y_dim));
	return (map);
}*/

t_map	*map_ptmap_init(t_map *map) //ESTO CAMBIA
{
	//int			x;
	int	 		y;
	//t_dll		*ptnode;

	//ptnode = *ptlst;
	map->map = (t_pt **)malloc(sizeof(t_pt *) * map->y_dim);
	if (!map->map)
		return (NULL);
	y = 0;
	while (y < map->y_dim)
	{
		map->map[y] = (t_pt*)malloc(sizeof(t_pt) * map->x_dim);
		if (!map->map[y])
			return ((t_map *)map_evalerror_ptmap(map, y));
		/*x = 0;
		while (x < map->x_dim) //este while no sería necesaria, el ptmap ya está iniciado
		{
			ptnode = map_getptinfo(ptnode, map, x, y);
			x++;
		}*/
		y++;
	}
	/*if (ptnode)
		return ((t_map *)map_evalerror_ptmap(map, map->y_dim));*/
	return (map);
}

static int	map_size_space(char *txt)
{
	int			count;
	int			i;
	const char	*dict_m = "0123456789abcdefx,";
	const char	*dict_M = "0123456789ABCDEFX,";

	i = -1;
	count = 0;
	while (txt[++i] != '\0')
	{
		if ((ft_strchr(dict_m, txt[i]) != 0 || ft_strchr(dict_M, txt[i]) != 0)
			&& (txt[i + 1] == ' ' || txt[i + 1] == '\0'))
			count++;
	}
	return (count);
}

t_map	*map_size(char *txt, t_map *map)
{
	const int	txt_size = map_size_space(txt);
	
	map->y_dim = ft_strchr_count(txt, '\n');
	if (map->y_dim == 0 || txt_size == 0)
	{
		map->map = map_evalerror_ptmap(map, 0);
		return (NULL);
	}
	map->x_dim = ((txt_size + (1*map->y_dim)) / map->y_dim);
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

t_map	*fdf_init(char *txt)
{
	t_map		*map;
	
	map = (t_map*)map_init();
	if (!map)
		return (NULL);
	map = map_size(txt, map);
	if (!map)
		return (NULL);
	map = map_ptmap_init(map);
	if (!map)
		return (NULL);
	map = (t_map *)a_parse2(txt, (void *)map);
	if (!map)
		return (NULL);
	//pt_print(map->map, map->y_dim, map->x_dim); //TODO: delete
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
