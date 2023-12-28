/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:46:00 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/28 14:46:25 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUTOMATA_H
# define AUTOMATA_H

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"

typedef struct s_pointcloud
{
	t_dll	*ptlist;
	int		xdim;
	int		ydim;
}	t_ptcloud;

typedef struct s_ptcontent
{
	int	height;
	int	color;
}	t_ptcont;

size_t	a_getstate(int i, int j);
size_t	a_changestate(char c, size_t state);
t_dll	**a_parse(char *s, t_dll **ptlst);

#endif