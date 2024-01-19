/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_putcolor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 13:35:43 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/19 13:35:45 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*static int	fdf_getmaxdif(int dx, int dy)
{
	if (dx >= dy)
		return (dx);
	return (dy);
}*/

int	*fdf_putcolor_x(t_pt *pt1, t_pt *pt2)
{
	const int	steps = (pt2->px_xy[0] - pt1->px_xy[0]); //dx >= dy
	int			*colors;
	int			c1[3];
	int			c2[3];
	int			i;
	double		r;
	double		g;
	double		b;
	double		f;

	colors = (int *)malloc(sizeof(int) * steps);
	if (!colors)
		return (NULL); //will need to free everything
	c1[0] = pt1->color >> 16 & 0xff; //R
	c1[1] = pt1->color >> 8 & 0xff; //G
	c1[2] = pt1->color & 0xff; //B
	c2[0] = pt2->color >> 16 & 0xff; //R
	c2[1] = pt2->color >> 8 & 0xff; //G
	c2[2] = pt2->color & 0xff; //B

	i = 0;
	if (pt1->color <= pt2->color)
	{
		while (i < steps)
		{
			f = (double)(i / (double)(steps - 1));
			r = c1[0] - (f * (double)(c2[0] - c1[0]));
			g = c1[1] - (f * (double)(c2[1] - c1[1]));
			b = c1[2] - (f * (double)(c2[2] - c1[2]));
			colors[i] = (((int)r << 16) | ((int)g << 8) | (int)b);
			i++;
		}
	}
	else if (pt1->color > pt2->color)
	{
		while (i < steps)
		{
			f = (double)(i / (double)(steps - 1));
			r = c1[0] + (f * (double)(c2[0] - c1[0]));
			g = c1[1] + (f * (double)(c2[1] - c1[1]));
			b = c1[2] + (f * (double)(c2[2] - c1[2]));
			colors[i] = (((int)r << 16) | ((int)g << 8) | (int)b);
			i++;
		}
	}

	//print colors
	i = 0;
	while (i < steps)
	{
		printf("c: %d\n", colors[i]);
		i++;
	}
	printf("\n\n");
	return (colors);
}

