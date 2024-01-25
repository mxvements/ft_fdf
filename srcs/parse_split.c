/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:37:05 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/25 13:37:20 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	*txt_evalpoint(char *ptinfo, t_pt *pt, int x, int y)
{
	int			atoiflag;
	const int	comma_i = ft_strchri(ptinfo, ',');

	atoiflag = 0;
	pt->xyz[0] = x;
	pt->xyz[1] = y;
	pt->xyz[2] = ft_atoif(ptinfo, &atoiflag) / ZSCALE;
	if (atoiflag < 0)
		return (NULL);
	if (comma_i != -1)
		pt->color = ft_atoh(ptinfo + comma_i + 1);
	else
		pt->color = 0xFFFFFF;
	return ((void *)pt);
}

t_map	*txt_parse(char *txt, t_map *map)
{
	char	**parse_y;
	char	**parse_x;
	int		y;
	int		x;

	parse_y = ft_split(txt, '\n');
	y = -1;
	while (parse_y[++y] != NULL)
	{
		parse_x = ft_split(parse_y[y], ' ');
		x = -1;
		while (parse_x[++x] != NULL)
		{
			if (txt_evalpoint(parse_x[x], &(map->map[y][x]), x, y) == NULL)
				return (map_evalerror_ptmap(map, y));
		}
	}
	if (x != map->x_dim || y != map->y_dim)
		return (map_evalerror_ptmap(map, y));
	return (map);
}
