/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:55:41 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/08 22:47:37 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_show_menu(void)
{
	write(1, ANSICOLOR_CYAN, 6);
	ft_putstr_fd("*************** fdf ***************\n", 1);
	ft_putstr_fd("Press (ESC) to close window\n", 1);
	ft_putstr_fd("Press (r) to rotate (WIP)\n", 1);
	ft_putstr_fd("Press (s) to scale (WIP)\n", 1);
	ft_putstr_fd("Press (t) to translate (WIP)\n", 1);
	write(1, ANSICOLOR_RESET, 5);
}

int	fdf_handle_input(int keysym, t_mlx *mlx_data)
{
	write(1, ANSICOLOR_GREEN, 6);
	if (keysym == KEY_ESC)
	{
		write(1, "(EXC)\n", 6);
		mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
		write(1, ANSICOLOR_RESET, 5);
		return (1);
	}
	printf("Key: (%d)\n", keysym);
	write(1, ANSICOLOR_RESET, 5);
	return (0);
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

void	fdf_lineBresenham_opc1(int *p1, int *p2, t_map *map)
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
		x += ((p2[0] - p1[0]) / dx);
		if (p < 0)
			p = p + (2 * dy);
		else
		{
			p = p + (2 * (dy - dx));
			y += ((p2[1] - p1[1]) / dy);
		}
	}
}

void	fdf_lineBresenham_opc2(int *p1, int *p2, t_map *map)
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
		y += ((p2[1] - p1[1]) / dy);
		if (p < 0)
			p = p + (2 * dx);
		else
		{
			p = p + (2 * (dx - dy));
			x += ((p2[0] - p1[0]) / dx);
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
			fdf_lineBresenham_opc1(pt1->px_xy, pt2->px_xy, map);
		if ((pt1->px_xy[0] > pt2->px_xy[0]))
			fdf_lineBresenham_opc1(pt2->px_xy, pt1->px_xy, map);
	}
	else if( dy > dx)
	{
		//opcion 2, y crece antes que x
		if (pt1->px_xy[0] <= pt2->px_xy[0])
			fdf_lineBresenham_opc2(pt1->px_xy, pt2->px_xy, map);
		if (pt1->px_xy[0] > pt2->px_xy[0])
			fdf_lineBresenham_opc2(pt2->px_xy, pt1->px_xy, map);
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