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
	write(1, ANSICOLOR_BLUE, 6);
	ft_putstr_fd("********************** fdf **********************\n", 1);
	ft_putstr_fd("Press (ESC) to close window\n", 1);
	ft_putstr_fd("Press (r) to rotate (WIP)\n", 1);
	ft_putstr_fd("Press (s) to scale (WIP)\n", 1);
	ft_putstr_fd("Press (t) to translate (WIP)\n", 1);
	write(1, ANSICOLOR_RESET, 5);
}

int	fdf_key_input(int keysym, t_mlx *mlx_data)
{
	static int key_tr;

	if (!key_tr)
		key_tr = 0;
	if (keysym == KEY_ESC)
		return (fdf_handle_input_ESC(mlx_data));
	if (key_tr == 0 && (keysym == KEY_r || keysym == KEY_s || keysym == KEY_t))
	{
		write(1, ANSICOLOR_CYAN, 6);
		key_tr = fdf_handle_input_RST(keysym);
		write(1, ANSICOLOR_RESET, 5);
		return (key_tr);
	}
	if (keysym == KEY_x || keysym == KEY_y || keysym == KEY_z)
		return (fdf_handle_input_XYZ(keysym, key_tr));
	if (fdf_is_key_nbr(keysym, key_tr) != -1)
		return (fdf_is_key_nbr(keysym, key_tr));
	if (keysym == KEY_F1)
		return (keysym);
	write(1, ANSICOLOR_GRAY, 6);
	printf("Key: (%d)\n", keysym);
	write(1, ANSICOLOR_RESET, 5);
	return (key_tr);
}

int	fdf_handle_input_ESC(t_mlx *mlx_data)
{
	write(1, ANSICOLOR_MAGENTA, 6);
	write(1, "(EXC)\n", 6);
	mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
	write(1, ANSICOLOR_RESET, 5);
	return (-1);
}

int	fdf_handle_input_RST(int keysym)
{
	if (keysym == KEY_r)
	{
		ft_putstr_fd("********************** rot **********************\n", 1);
		ft_putstr_fd("Press (x) to rotate the X axis\n", 1);
		ft_putstr_fd("Press (y) to rotate the Y axis\n", 1);
		ft_putstr_fd("Press (z) to rotate the Z axis\n", 1);
		return ('r');
	}
	if (keysym == KEY_s)
	{
		ft_putstr_fd("********************** scl **********************\n", 1);
		ft_putstr_fd("Press number to scale on the X axis\n", 1);
		return ('s');
	}
	if (keysym == KEY_t)
	{
		ft_putstr_fd("********************** mov **********************\n", 1);
		ft_putstr_fd("Press (x) to move on the X axis\n", 1);
		ft_putstr_fd("Press (y) to move on the Y axis\n", 1);
		ft_putstr_fd("Press (z) to move on the Z axis\n", 1);
		return ('t');
	}
	return (0);
}

int	fdf_handle_input_XYZ(int keysym, int key_transf)
{
	if (key_transf == 'r' || key_transf == 's' || key_transf == 't')
	{
		if (keysym == KEY_x)
			return ('x');
		if (keysym == KEY_y)
			return ('y');
		if (keysym == KEY_z)
			return ('z');
	}
	else
	{
		write(1, ANSICOLOR_MAGENTA, 6);
		ft_putstr_fd("Press R-S-T to choose transformation first\n", 1);
		write(1, ANSICOLOR_RESET, 5);
	}
	return (0);
}

int	fdf_is_key_nbr(int keysym, int key_transf)
{
	if (key_transf == 'x' || key_transf == 'y' || key_transf == 'z')
	{
		if (keysym == KEY_0)
			return (0);
		if (keysym == KEY_1)
			return (1);
		if (keysym == KEY_2)
			return (2);
		if (keysym == KEY_3)
			return (3);
		if (keysym == KEY_4)
			return (4);
		if (keysym == KEY_5)
			return (5);
		if (keysym == KEY_6)
			return (6);
		if (keysym == KEY_7)
			return (7);
		if (keysym == KEY_8)
			return (8);
		if (keysym == KEY_9)
			return (9);
	}
	return (-1);
}
