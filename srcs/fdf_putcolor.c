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

static int	*fdf_putcolor_interp(int steps, int c_vw[2][3], double f)
{
	int			i;
	double		r;
	double		g;
	double		b;
	int			*colors;

	colors = (int *)malloc(sizeof(int) * steps);
	if (!colors)
		return (NULL);
	i = 0;
	while (i < steps)
	{
		r = c_vw[0][0] + ((double)(i * f) *(double)(c_vw[1][0] - c_vw[0][0]));
		g = c_vw[0][1] + ((double)(i * f) *(double)(c_vw[1][1] - c_vw[0][1]));
		b = c_vw[0][2] + ((double)(i * f) *(double)(c_vw[1][2] - c_vw[0][2]));
		colors[i] = (((int)r << 16) | ((int)g << 8) | (int)b);
		i++;
	}
	return (colors);
}

int	*fdf_putcolor_x(t_pt *pt1, t_pt *pt2)
{
	const int	steps = abs((pt2->px_xy[0] - pt1->px_xy[0]));
	double		f;
	int			c_vw[2][3];
	int			c_pt[2];

	if (pt1->px_xy[0] <= pt2->px_xy[0])
	{
		c_pt[0] = pt1->color;
		c_pt[1] = pt2->color;
	}
	else if (pt2->px_xy[0] < pt1->px_xy[0])
	{
		c_pt[0] = pt2->color;
		c_pt[1] = pt1->color;
	}
	c_vw[0][0] = c_pt[0] >> 16 & 0xff;
	c_vw[0][1] = c_pt[0] >> 8 & 0xff;
	c_vw[0][2] = c_pt[0] & 0xff;
	c_vw[1][0] = c_pt[1] >> 16 & 0xff;
	c_vw[1][1] = c_pt[1] >> 8 & 0xff;
	c_vw[1][2] = c_pt[1] & 0xff;
	f = (double)(1 / (double)(steps - 1));
	return (fdf_putcolor_interp(steps, c_vw, f));
}

int	*fdf_putcolor_y(t_pt *pt1, t_pt *pt2)
{
	const int	steps = abs((pt2->px_xy[1] - pt1->px_xy[1]));
	double		f;
	int			c_vw[2][3];
	int			c_pt[2];

	if (pt1->px_xy[0] <= pt2->px_xy[0])
	{
		c_pt[0] = pt1->color;
		c_pt[1] = pt2->color;
	}
	else if (pt2->px_xy[0] < pt1->px_xy[0])
	{
		c_pt[0] = pt2->color;
		c_pt[1] = pt1->color;
	}
	c_vw[0][0] = c_pt[0] >> 16 & 0xff;
	c_vw[0][1] = c_pt[0] >> 8 & 0xff;
	c_vw[0][2] = c_pt[0] & 0xff;
	c_vw[1][0] = c_pt[1] >> 16 & 0xff;
	c_vw[1][1] = c_pt[1] >> 8 & 0xff;
	c_vw[1][2] = c_pt[1] & 0xff;
	f = (double)(1 / (double)(steps - 1));
	return (fdf_putcolor_interp(steps, c_vw, f));
}

int	*fdf_putcolor_wrapper(t_pt *pt1, t_pt *pt2, const int dx, const int dy)
{
	if (dx >= dy)
		return (fdf_putcolor_x(pt1, pt2));
	else if (dy > dx)
		return (fdf_putcolor_y(pt1, pt2));
	return (NULL);
}
