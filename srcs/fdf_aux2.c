/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_aux2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:33:24 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/12 11:33:26 by luciama2         ###   ########.fr       */
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

void	fdf_show_transformation(t_keyin *keys)
{
	const int	transf = keys->key_tr;
	const int	axis = keys->key_ax;
	const int	nbr = keys->key_nbr;

	write(1, ANSICOLOR_MAGENTA, 6);
	if (transf == 'r')
		ft_putstr_fd("+ ROTATING in ", 1);
	else if (transf == 's')
		ft_putstr_fd("+ SCALING ", 1);
	else if (transf == 't')
		ft_putstr_fd("+ TRASLATING in ", 1);
	if (axis == 'x')
		ft_putstr_fd("axis (X) ", 1);
	else if (axis == 'y')
		ft_putstr_fd("axis (Y) ", 1);
	else if (axis == 'z')
		ft_putstr_fd("axis (Z) ", 1);
	ft_putnbr_fd(nbr, 1);
	ft_putstr_fd("px\n", 1);
	write(1, ANSICOLOR_RESET, 5);
}

int	fdf_handle_input_rst(int keysym)
{
	write(1, ANSICOLOR_RESET, 5);
	write(1, ANSICOLOR_BLUE, 6);
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

int	fdf_handle_input_xyz(int keysym, t_keyin *keys)
{
	const int	transf = keys->key_tr;
	int			axis;

	write(1, ANSICOLOR_BLUE, 6);
	axis = 0;
	if (transf == 's') //TODO: change to case-switch as it would be more readable
		return (axis);
	if (keysym == KEY_x)
		axis = 'x';
	else if (keysym == KEY_y)
		axis = 'y';
	else if (keysym == KEY_z)
		axis = 'z';
	if (transf == 'r')
		ft_putstr_fd("+ Press (nbrs) to ROTATE ", 1);
	if (transf == 't')
		ft_putstr_fd("+ Press (nbrs) to MOVE ", 1);
	if (axis == 'x')
		ft_putstr_fd("on the X axis\n", 1);
	else if (axis == 'y')
		ft_putstr_fd("on the Y axis\n", 1);
	else if (axis == 'z')
		ft_putstr_fd("on the Z axis\n", 1);
	write(1, ANSICOLOR_RESET, 5);
	return (axis);
}

int	fdf_is_input_nbr(int keysym)
{
	int	nbr;

	nbr = -1;
	write(1, ANSICOLOR_RESET, 5);
	if (keysym == KEY_0)
		nbr = 0;
	if (keysym == KEY_1)
		nbr = 1;
	if (keysym == KEY_2)
		nbr = 2;
	if (keysym == KEY_3)
		nbr = 3;
	if (keysym == KEY_4)
		nbr = 4;
	if (keysym == KEY_5)
		nbr = 5;
	if (keysym == KEY_6)
		nbr = 6;
	if (keysym == KEY_7)
		nbr = 7;
	if (keysym == KEY_8)
		nbr = 8;
	if (keysym == KEY_9)
		nbr = 9;
	return (nbr);
}
