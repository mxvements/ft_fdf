/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:48:55 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/22 13:49:02 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* state matrix:
    // (j)
	//   0  1  2  3  4
	//	/s,-+, D, \n, ^		// 	(i)
		{4, 2, 3, 4, 1},	//	0	INIT
		{1, 1, 1, 1, 1},	//	1	ERR
		{1, 1, 3, 1, 1},	//	2	SIGN '-' '+'
		{4, 1, 3, 4, 1},	//	3	DICT "0123456789abcdefx,"
		{4, 2, 3, 4, 1}		//	4	SPACE or \n

*/
size_t	a_getstate(int i, int j)
{
	const size_t	t_states[][5] = {\
		{4, 2, 3, 4, 1}, \
		{1, 1, 1, 1, 1}, \
		{1, 1, 3, 1, 1}, \
		{4, 1, 3, 4, 1}, \
		{4, 2, 3, 4, 1} \
	};

	return (t_states[i][j]);
}

size_t	a_changestate(char c, size_t state)
{
	size_t		ostate;
	const char	*dict_m = "0123456789abcdefx,";
	const char	*dict_mm = "0123456789ABCDEFX,";

	if (c == ' ')
		ostate = a_getstate(state, 0);
	else if (ft_issign(c) != 0)
		ostate = a_getstate(state, 1);
	else if (ft_strchr(dict_m, c) != 0 || ft_strchr(dict_mm, c) != 0)
		ostate = a_getstate(state, 2);
	else if (c == '\n')
		ostate = a_getstate(state, 3);
	else
		ostate = a_getstate(state, 4);
	return (ostate);
}

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

t_map	*a_parse(char *txt, t_map *map)
{
	int			i;
	size_t		state;
	size_t		ostate;
	size_t		init_pt;
	static int	xy[2];

	i = -1;
	state = 0;
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
