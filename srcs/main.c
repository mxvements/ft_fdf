/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 16:58:27 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/25 20:01:10 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*readfile(char *path)
{
	char	*txt;
	char	*gnl;
	char	*tmp;
	int		fd;

	txt = NULL;
	fd = open(path, O_RDONLY);
	while(1)
	{
		gnl = get_next_line(fd);
		if (gnl == NULL)
			break ;
		if (!txt)
			txt = gnl;
		else
		{
			tmp = ft_strjoin(txt, gnl);
			free(txt);
			free(gnl);
			txt = tmp;
		}
	}
	close(fd);
	return (txt);
}

int main(void)
{
	char	*path = "./test_maps/42.fdf";
	char	*txt;

	txt = readfile(path);
	printf("%s\n", txt);

	/*
	** TODO:
	** - must create a t_dll **ptlst to start parsing
	** - get matrix dimensions from txt
	** - put list info on matrix (and free list)
	** - update pt info with x and y from matrix
	*/

	return (0);
}