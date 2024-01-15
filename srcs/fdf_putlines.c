/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_putlines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:06:04 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/10 14:06:05 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_lineBresenham_x(int *p1, int *p2, t_map *map)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		p;

	x = p1[0];
	y = p1[1];
	dx = abs((p2[0] - p1[0]));
	dy = abs((p2[1] - p1[1]));
	p = (2 * dy) - dx;
	while ((x - p1[0]) * (x - p2[0]) <= 0)
	{
		if (x < WIDTH && y < HEIGHT)
			fdf_pixelput(&(map->mlx_data), x, y, 0xFF); //COLOR?
		x += ((p2[0] - p1[0]) / dx); //!DIV0
		if (p < 0)
			p = p + (2 * dy);
		else
		{
			p = p + (2 * (dy - dx));
			y += ((p2[1] - p1[1]) / dy);//!DIV0
		}
	}
}

void	fdf_lineBresenham_y(int *p1, int *p2, t_map *map)
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	int		p;

	x = p1[0];
	y = p1[1];
	dx = abs((p2[0] - p1[0]));
	dy = abs((p2[1] - p1[1]));
	p = (2 * dx) - dy;
	while ((y - p1[1]) * (y - p2[1]) <= 0)
	{
		if (x < WIDTH && y < HEIGHT)
			fdf_pixelput(&(map->mlx_data), x, y, 0xFF); //COLOR?
		y += ((p2[1] - p1[1]) / dy);//!DIV0
		if (p < 0)
			p = p + (2 * dx);
		else
		{
			p = p + (2 * (dx - dy));
			x += ((p2[0] - p1[0]) / dx);//!DIV0
		}
	}
}

void	fdf_lineBresenham_wrapper(t_map *map, t_pt *pt1, t_pt *pt2)
{
	const int	dx = abs(pt1->px_xy[0] - pt2->px_xy[0]);
	const int	dy = abs(pt1->px_xy[1] - pt2->px_xy[1]);
	
	/*printf("fdf_lineBresenham_Wrapper: \n");
	printf("pt1: (%d, %d, %d) en (%d, %d)\n", pt1->xyz[0], pt1->xyz[1], pt1->xyz[2], pt1->px_xy[0], pt1->px_xy[1]);
	printf("pt2: (%d, %d, %d) en (%d, %d)\n", pt2->xyz[0], pt2->xyz[1], pt1->xyz[2], pt2->px_xy[0], pt2->px_xy[1]);
	*/
	if (dx >= dy)
	{
		//opcion 1. x crece antes que y
		if ((pt1->px_xy[0] <= pt2->px_xy[0]))
			fdf_lineBresenham_x(pt1->px_xy, pt2->px_xy, map);
		if ((pt1->px_xy[0] > pt2->px_xy[0]))
			fdf_lineBresenham_x(pt2->px_xy, pt1->px_xy, map);
	}
	else if( dy > dx)
	{
		//opcion 2, y crece antes que x
		if (pt1->px_xy[0] <= pt2->px_xy[0])
			fdf_lineBresenham_y(pt1->px_xy, pt2->px_xy, map);
		if (pt1->px_xy[0] > pt2->px_xy[0])
			fdf_lineBresenham_y(pt2->px_xy, pt1->px_xy, map);
	}

	
}

void	fdf_putlines(t_map *map, int x, int y)
{
	t_pt	*pt;
	t_pt	*pt_right;
	t_pt	*pt_down;

	pt = &(map->map[y][x]);
	if (x != (map->x_dim - 1))
	{
		pt_down = &(map->map[y][x + 1]);
		fdf_lineBresenham_wrapper(map, pt, pt_down);
	}
	if (y != (map->y_dim - 1))
	{
		pt_right = &(map->map[y + 1][x]);
		fdf_lineBresenham_wrapper(map, pt, pt_right);
	}			
}

void	fdf_pixelput(t_mlx *mlx, int x, int y, int color)
{
	int		dist;
	int		line_length;
	int 	bpp;
	
	line_length = mlx->line_len;
	bpp = mlx->bpp;
	dist = (y * line_length) + (x * (bpp / 8));
	*((unsigned int*)(dist + mlx->img_addr)) = color;
}