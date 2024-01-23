/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:23:17 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/23 11:23:19 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*arr_evalpoint(char *s, t_map *map, int *x, int *y)
{
	int			comma;
	const int	sp = ft_strchri(s, ' ');
	int			atoiflag;
	char		*ss;

	if (!map)
		return (NULL);
	ss = ft_substr(s, 0, sp + 1);
	comma = ft_strchri(ss, ',');
	atoiflag = 0;
	(map->map[*y][*x]).xyz[0] = *x;
	(map->map[*y][*x]).xyz[1] = *y;
	(map->map[*y][*x]).xyz[2] = ft_atoif(s, &atoiflag) / ZSCALE;
	if (atoiflag < 0)
		return (map_evalerror_ptmap(map, map->y_dim));
	if (comma != -1)
		(map->map[*y][*x]).color = ft_atoh(s + comma + 1);
	else
		(map->map[*y][*x]).color = 0xFFFFFF;
	free(ss);
	return (map);
}
