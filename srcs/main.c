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

/*void	leaks(void)
{
	system("leaks -q fdf");
}*/

static int	checkfile(char *path)
{
	const size_t	len = ft_strlen(path);
	const char		*filetype = (path + (len - 4));

	return (ft_strncmp(filetype, ".fdf", 4));
}

//atexit(leaks);
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (checkfile(argv[1]) != 0)
		{
			write(1, ANSICOLOR_RED, 6);
			ft_putstr_fd("Error. Wrong file ending.\n", 2);
			write(1, ANSICOLOR_RED, 5);
			return (-1);
		}
		fdf(argv[1]);
	}
	else if (argc > 2)
	{
		write(1, ANSICOLOR_RED, 6);
		ft_putstr_fd("Error. Arguments: \"./fdf ./file.fdf\"\n", 2);
		write(1, ANSICOLOR_RESET, 5);
	}
	return (0);
}
