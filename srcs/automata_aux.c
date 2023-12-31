/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 19:18:22 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/31 19:26:49 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	lst_print(t_dll **head)
{
	t_ptcont	*cntnt;
	t_dll		*ptnode;
	int			i;

	ptnode = *head;
	i = 0;
	while (ptnode)
	{
		cntnt = ptnode->content;
		write(1, "(", 1);
		ft_putnbr_fd(i, 1);
		write(1, ") ", 2);
		ft_putnbr_fd(cntnt->height, 1);
		write(1, "//", 2);
		ft_putnbr_fd(cntnt->color, 1);
		write(1, "\n", 1);
		i++;
		ptnode = ptnode->next;
	}
	return ;
}

t_dll	**lst_init(void)
{
	t_dll	**ptlst;

	ptlst = (t_dll**)malloc(sizeof(t_dll*));
	if (!ptlst)
		return (NULL);
	*ptlst = NULL;
	return (ptlst);
}