/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:55:41 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/06 00:03:43 by lmmielgo         ###   ########.fr       */
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

void	fdf_lineBresenham_opc1(int *p1, int *p2, t_map *map, int sx, int sy)
{
	int			x;
	int			y;
	int	dx = (p2[0] - p1[0]);
	int	dy = (p2[1] - p1[1]);
	int p;

	x = p1[0];
	y = p1[1];
	dx = abs(dx);
	dy = abs(dy);
	p = (2 * dy) - dx;
	while ((x - p1[0]) * (x - p2[0]) <= 0)
	{
		if (x <= WIDTH && y <= HEIGHT)
			fdf_pixelput(&(map->mlx_data), x, y, 0xFF); //COLOR?
		x += sx;
		if (p < 0)
			p = p + (2 * dy);
		else
		{
			p = p + (2 * (dy - dx));
			y += sy;
		}
	}
}

void	fdf_lineBresenham_opc2(int *p1, int *p2, t_map *map)
{
	int			x;
	int			y;
	int	dx = (p2[0] - p1[0]);
	int	dy = (p2[1] - p1[1]);
	int sign_dx = (dx > 0) ? 1 : -1;
    int sign_dy = (dy > 0) ? 1 : -1;
	int p;

	x = p1[0];
	y = p1[1];
	dx = abs(dx);
	dy = abs(dy);
	p = (2 * dx) - dy;
	while (y != p2[1])
	{
		fdf_pixelput(&(map->mlx_data), x, y, 0xFF); //COLOR?
		y += sign_dy; // THIS IS for the way the pixels
		if (p < 0)
			p = p + (2 * dx);
		else
		{
			p = p + (2 * (dx - dy));
			x += sign_dx;
		}
	}
}

void	fdf_lineBresenham_wrapper(t_map *map, t_pt *pt1, t_pt *pt2)
{
	int	dx;
	int	dy;
	int sign_dx;
    int sign_dy;

	dx = (pt2->px_xy[0] - pt1->px_xy[0]);
	dy = (pt2->px_xy[1] - pt1->px_xy[1]);
	sign_dx = 1;
	if (dx < 0)
		sign_dx = -1;
	sign_dy = 1;
	if (dy < 0)
		sign_dy = -1;
	fdf_lineBresenham_opc1(pt1->px_xy, pt2->px_xy, map, sign_dx, sign_dy);
	/*/
	if ((pt1->vw_xyz[0] < pt2->vw_xyz[0]) && (pt1->vw_xyz[1] < pt2->vw_xyz[1]))
		fdf_lineBresenham_opc1(pt1->px_xy, pt2->px_xy, map);
	if ((pt1->vw_xyz[0] < pt2->vw_xyz[0]) && (pt2->vw_xyz[1] < pt1->vw_xyz[1]))
		fdf_lineBresenham_opc1(pt1->px_xy, pt2->px_xy, map);
	if((pt2->vw_xyz[0] < pt1->vw_xyz[0]) && (pt2->vw_xyz[1] < pt1->vw_xyz[1]))
		fdf_lineBresenham_opc1(pt2->px_xy, pt1->px_xy, map);
	if ((pt2->vw_xyz[0] < pt1->vw_xyz[0]) && (pt1->vw_xyz[1] < pt2->vw_xyz[1]))
		fdf_lineBresenham_opc1(pt2->px_xy, pt1->px_xy, map);*/
}

void	fdf_putlines(t_map *map, int x, int y)
{
	t_pt	*pt;
	t_pt	*pt_right;
	t_pt	*pt_down;

	pt = &(map->map[x][y]);
	if (y != (map->y_dim - 1))
	{
		pt_down = &(map->map[x][y + 1]);
		fdf_lineBresenham_wrapper(map, pt, pt_down);
	}
	if (x != (map->x_dim - 1))
	{
		pt_right = &(map->map[x + 1][y]);
		fdf_lineBresenham_wrapper(map, pt, pt_right);
	}			
}