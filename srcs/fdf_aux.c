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
	ft_putstr_fd("Press (r) to rotate\n", 1);
	ft_putstr_fd("Press (s) to scale\n", 1);
	ft_putstr_fd("Press (t) to translate\n", 1);
	ft_putstr_fd("Press (i) to reset view to isometric\n", 1);
	ft_putstr_fd("Press (p) to reset view to plan\n", 1);
	ft_putstr_fd("Use arrows to move view\n", 1);
	ft_putstr_fd("Use keypad's -+ to move zoom out/in\n", 1);
	ft_putstr_fd("Use mouse's wheel to move zoom out/in\n", 1);
	ft_putstr_fd("Use mouse's righnt-click to rotate view\n", 1);
	write(1, ANSICOLOR_RESET, 5);
}

void	fdf_show_transformation(t_keyin *keys)
{
	const int	transf = keys->key_tr;
	const int	axis = keys->key_ax;
	const int	nbr = keys->key_nbr * keys->key_sign;

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
