/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:55:41 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/12 00:21:54 by lmmielgo         ###   ########.fr       */
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

int	fdf_change_map(void)
{
	printf("change map\n");
	return (0);
}

int	fdf_key_input(int keysym, t_map *map)
{
	static int	key_tra;
	static int	key_ax;
	static int	key_nbr;

	if (!key_tra)
		key_tra = 0;
	if (!key_ax)
		key_ax = 0;
	if (!key_nbr)
		key_nbr = 0;
	write(1, ANSICOLOR_RESET, 5);
	if (keysym == KEY_ESC)
		return (fdf_handle_input_ESC(map));
	if (key_tra == 0 && (keysym == KEY_r || keysym == KEY_s || keysym == KEY_t))
		key_tra = fdf_handle_input_RST(keysym);
	if ((key_ax == 0 && key_tra != 0)
		&& (keysym == KEY_x || keysym == KEY_y || keysym == KEY_z))
		key_ax = fdf_handle_input_XYZ(keysym);
	if ((key_ax != 0 && key_tra != 0) && (fdf_handle_input_NBR(keysym) != -1))
	{
		key_nbr *= 10;
		key_nbr += fdf_handle_input_NBR(keysym);
	}
	if (keysym == KEY_ENTER)
		return (fdf_change_map());
	return (keysym);
}

int	fdf_handle_input_ESC(t_map *map)
{
	t_mlx	*mlx_data;

	mlx_data = &(map->mlx_data);
	//FREE THINGS?
	write(1, ANSICOLOR_MAGENTA, 6);
	write(1, "(EXC)\n", 6);
	mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
	write(1, ANSICOLOR_RESET, 5);
	return (-1);
}

int	fdf_handle_input_RST(int keysym)
{
	write(1, ANSICOLOR_CYAN, 6);
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

int	fdf_handle_input_XYZ(int keysym)
{
	write(1, ANSICOLOR_CYAN, 6);
	if (keysym == KEY_x)
	{
		ft_putstr_fd("+ Press (nbrs) to move on the X axis\n", 1);
		return ('x');
	}
	if (keysym == KEY_y)
	{
		ft_putstr_fd("+ Press (nbrs) to move on the Y axis\n", 1);
		return ('y');
	}
	if (keysym == KEY_z)
	{
		ft_putstr_fd("+ Press (nbrs) to move on the Z axis\n", 1);
		return ('z');
	}
	return (0);
}

int	fdf_handle_input_NBR(int keysym)
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
	return (-1);
}
