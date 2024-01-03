/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:55:41 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/03 16:55:51 by luciama2         ###   ########.fr       */
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