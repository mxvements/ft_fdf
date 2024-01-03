/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_aux2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:06:19 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/03 17:06:27 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Must do some check view funct
** scale cannnot be 0
*/
void	arrint_scale(t_view *vw)
{
	int x;
	int y;

	x = 0;
	while (x < 3)
	{
		y = 0;
		while (y < 3)
		{
			vw->view[x][y] = vw->view[x][y] * vw->scale_factor;
			y++;
		}
		x++;
	}
}

void	arrint_translate(t_view *vw)
{
	int	x;
	int y;

	x = 0;
	while (x < 3)
	{
		vw->view[x][x] = vw->view[x][x] + vw->move_dist;
		x++;
	}
}

