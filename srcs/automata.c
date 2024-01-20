/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 16:41:51 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/31 23:19:58 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*lst_evalerror(t_dll **ptlst)
{
	if ((*ptlst))
		ft_dllfree(ptlst);
	if (ptlst)
	{
		free(ptlst);
		*ptlst = NULL;
	}
	write(1, ANSICOLOR_RED, 6);
	ft_putstr_fd("Error.\n", 2);
	write(1, ANSICOLOR_RESET, 5);
	return (NULL);
}

t_dll	**lst_evalpoint(char *s, t_dll **ptlst)
{
	const int	comma = ft_strchri(s, ',');
	int			atoiflag;
	t_ptcont	*ptinfo;
	t_dll		*ptnode;

	if (!s)
		return (NULL); //need to protect the previous substr
	atoiflag = 0;
	ptinfo = (t_ptcont *)malloc(sizeof(t_ptcont));
	if (!ptinfo)
		return (lst_evalerror(ptlst));
	ptinfo->height = ft_atoif(s, &atoiflag);
	if (atoiflag < 0)
		return (lst_evalerror(ptlst));
	if (comma != -1)
	{
		ptinfo->color = ft_atoh(s + comma + 1);
		printf("color: %d\n", ptinfo->color); //TODO: borrar
	}
	else
		ptinfo->color = 0xFFFFFF; //TODO: default color blue
	ptnode = ft_dllnew((void *)ptinfo);
	if (!ptnode)
		return (lst_evalerror(ptlst));
	ft_dlladd_back(ptlst, ptnode);
	free(s);
	return (ptlst);
}

size_t	a_getstate(int i, int j)
{
	const size_t	t_states[][5] = {\
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

size_t	a_changestate(char c, size_t state)
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
}

t_dll	**a_parse(char *txt, t_dll **ptlst)
{
	size_t	i;
	size_t	state;
	size_t	ostate;
	size_t	init_pt;

	i = 0;
	state = 0;
	while (txt[i] != '\0')
	{
		ostate = a_changestate(txt[i], state);
		if ((state == 0 || state == 4) && (ostate == 2 || ostate == 3))
			init_pt = i;
		if ((state == 3 && ostate == 4) || (ostate == 3 && txt[i + 1] == '\0'))
		{
			ptlst = lst_evalpoint(ft_substr(txt, init_pt, (i - init_pt) + 1), ptlst);
			if (!ptlst)
				return (NULL);
		}
		if (ostate == 1 || (ostate < 3 && txt[i + 1] == '\0'))
			ptlst = lst_evalerror(ptlst);
		state = ostate;
		i++;
	}
	return (ptlst);
}
