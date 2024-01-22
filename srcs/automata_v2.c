/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:48:55 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/22 13:49:02 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map *arr_evalpoint(char *s, t_map *map, int *x, int *y)
{
	int			comma;
	const int	sp = ft_strchri(s, ' ');
	int			atoiflag;
	char		*ss;
	//t_pt		pt;
	///t_pt		**ptmap;

	if (!map)
		return (NULL);
	ss = ft_substr(s, 0, sp + 1);
	comma = ft_strchri(ss, ',');
	//ptmap = map->map;
	///pt = ptmap[*y][*x];
	atoiflag = 0;
	(map->map[*y][*x]).xyz[0] = *x;
	(map->map[*y][*x]).xyz[1] = *y;
	(map->map[*y][*x]).xyz[2] = ft_atoif(s, &atoiflag) / ZSCALE;
	if (atoiflag < 0)
		return (map_evalerror_ptmap(map, *x));
	if (comma != -1)
		(map->map[*y][*x]).color = ft_atoh(s + comma + 1);
	else
		(map->map[*y][*x]).color = 0xFFFFFF;
	free(ss);
	return (map);
}

/*
size_t	a_getstate(int i, int j) //OK
{
	const size_t	t_states[][6] = {\
	// (j)
	//   0  1  2  3  4
	//	/s,-+, D, \n, ^	// (i)
		{4, 2, 3, 4, 1},	//	0	INIT
		{1, 1, 1, 1, 1},	//	1	ERR
		{1, 1, 3, 1, 1},	//	2	SIGN '-' '+'
		{4, 1, 3, 4, 1},	//	3	DICT "0123456789abcdefx,"
		{4, 2, 3, 4, 1}		//	4	SPACE or \n
	};
	return (t_states[i][j]);
}

size_t	a_changestate(char c, size_t state, int *x, int *y) //OK
{
	size_t		ostate;
	const char	*dict_m = "0123456789abcdefx,";
	const char	*dict_M = "0123456789ABCDEFX,";

	if (c == ' ')
		ostate = a_getstate(state, 0);
	else if(ft_issign(c) != 0)
		ostate = a_getstate(state, 1);
	else if(ft_strchr(dict_m, c) != 0)
		ostate = a_getstate(state, 2);
	else if(ft_strchr(dict_M, c) != 0)
		ostate = a_getstate(state, 2);
	else if(c == '\n')
		ostate = a_getstate(state, 3);
	else
		ostate = a_getstate(state, 4);
	return (ostate);
}*/

static void	a_parse_updatecoord(int *x, int *y, int c)
{
	if (c == ' ')
		(*x)++;
	else if (c == '\n')
	{
		(*x) = 0;
		(*y)++;
	}
	return ;
}

static void	a_parse_initcoord(int *x, int *y)
{
	(*x) = 0;
	(*y) = 0;
}

t_map	*a_parse2(char *txt, t_map *map)
{
	int			i;
	size_t		state;
	size_t		ostate;
	size_t		init_pt;
	static int	xy[2];

	i = -1;
	state = 0;
	a_parse_initcoord(&(xy[0]), &(xy[1]));
	while (txt[++i] != '\0')
	{
		ostate = a_changestate(txt[i], state);
		if ((state == 0 || state == 4) && (ostate == 2 || ostate == 3))
			init_pt = i;
		if ((state == 3 && ostate == 4) || (ostate == 3 && txt[i + 1] == '\0'))
		{
			map = arr_evalpoint((txt + init_pt), map, &(xy[0]), &(xy[1]));
			a_parse_updatecoord(&(xy[0]), &(xy[1]), txt[i]);
		}
		if (ostate == 1 || (ostate < 3 && txt[i + 1] == '\0'))
			map = map_evalerror_ptmap(map, xy[0]);
		state = ostate;
	}
	return (map);
}
