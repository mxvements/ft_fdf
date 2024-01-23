/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 16:58:27 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/08 23:09:37 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	leaks(void)
{
	system("leaks -q fdf");
}

int main(int argc, char **argv)
{
	if (argc == 2 )
	{
		fdf(argv[1]);
	}
	else if (argc > 2)
	{
		write(1, ANSICOLOR_RED, 6);
		ft_putstr_fd("Error.\n", 2);
		write(1, ANSICOLOR_RESET, 5);
	}

	atexit(leaks);
	//system("leaks -q fdf");
	return (0);
}
