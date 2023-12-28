/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_automata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:41:51 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/28 16:41:54 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "automata.h"

t_dll	**evalerror(t_dll **ptlst)
{
	ft_dllfree(ptlst);
	ft_putstr_fd("Error\n", 2);
	free(ptlst);
	ptlst = NULL;
	return (ptlst);
}

t_dll	**evalpoint(char *s, t_dll **ptlst)
{
	const int	comma = ft_strchr(s, ',');
	int			atoiflag;
	t_ptcont	*ptinfo;
	t_dll		*pt;

	if (!s)
		return (NULL); //need to protect the previous substr
	atoiflag = 0;
	ptinfo = (t_ptcont *)malloc(sizeof(t_ptcont));
	if (!ptinfo)
		return (evalerror(ptlst));
	ptinfo->height = ft_atoif(s, &atoiflag);
	if (atoiflag < 0)
		return (evalerror(ptlst));
	/*if (comma != 0)
		//do color, starts in (s + comma)
	else
		//ptinfo->color == WHITE */
	pt = ft_dllnew((void *)ptinfo);
	if (!pt)
		return (evalerror(ptlst));
	ft_dlladd_back(ptlst, pt);	
	return (ptlst);
}

size_t	a_getstate(int i, int j)
{
	const size_t	t_states[][5] = {
	// (j)
	//	0  1  2  3  4
	//	/s, -+, D, \n, ^	// (i)
		{4, 2, 3, 4, 1},	//	0	INIT
		{1, 1, 1, 1, 1},	//	1	ERR
		{4, 1, 3, 4, 1},	//	2	SIGN '-' '+'
		{4, 1, 3, 4, 1},	//	3	DICT "0123456789abcdefx,"
		{4, 2, 3, 4, 1},	//	4	SPACE or \n
	};
	return (t_states[i][j]);
}

size_t	a_changestate(char c, size_t state)
{
	size_t		ostate;
	const char	*dict = "0123456789abcdefx,";

	if (c == ' ')
		ostate = a_getstate(state, 0);
	else if(ft_issign(c) != 0)
		ostate = a_getstate(state, 1);
	else if(ft_strchr(dict, c) != 0)
		ostate = a_getstate(state, 2);
	else if(c == '\n')
		ostate = a_getstate(state, 3);
	else
		ostate = a_getstate(state, 4);
	return (ostate);
}

t_dll	**a_parse(char *s, t_dll **ptlst)
{
	size_t	i;
	size_t	state;
	size_t	ostate;
	size_t	init_pt;

	i = 0;
	state = 0;
	while (s[i] != '\0')
	{
		ostate = a_changestate(s[i], state);
		if ((state == 0 || state == 4) && (ostate == 2 || ostate == 3))
			init_pt = i;
		if (state == 3 && (ostate == 4 || s[i] == '\0'))
		{
			ptlst = evalpoint(ft_substr(s, init_pt, (i - init_pt) + 1), ptlst);
			if (!ptlst)
				return (NULL);
		}
		if (ostate == 1 || (ostate < 3 && s[i] == '\0'))
			evalerror(ptlst);
		state = ostate;
		i++;
	}
	return (ptlst);
}
