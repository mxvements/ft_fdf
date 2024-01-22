/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:46:00 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/31 19:26:38 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOMATA_H
# define AUTOMATA_H

# include "fdf.h"
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

typedef struct s_ptcontent
{
	int	height;
	int	color;
}	t_ptcont;

//V1
//aux
void	lst_print(t_dll **head);
t_dll	**lst_init(void);
//eval info
t_dll	**lst_evalpoint(char *s, t_dll **ptlst);
void	*lst_evalerror(t_dll **ptlst);
//autoamata functs
t_dll	**a_parse(char *s, t_dll **ptlst);

size_t	a_getstate(int i, int j);
size_t	a_changestate(char c, size_t state);
//V2


#endif