/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 16:58:27 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/01 13:26:04 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "automata.h"

char	*readfile(char *path)
{
	char	*txt;
	char	*gnl;
	char	*tmp;
	int		fd;

	if (!(*path))
		return (NULL);
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

void	fdf(char *txt)
{
	t_dll	**ptlst;
	t_map	*map;
	
	//get list of point info from txt
	ptlst = lst_init();
	ptlst = a_parse(txt, ptlst);
	//MAP init
	map = map_init(ptlst, txt);
	//MAP print
	if (map)
		pt_print(map->map, map->x_dim, map->y_dim);
	//end MLX
	ft_dllfree(ptlst);
	free(ptlst);
	mlx_loop((map->mlx_data).mlx);
	free((map->mlx_data).mlx);
}

int main(void)
{
	char	*path = "./test_maps/simple_pyramid.fdf";
	char	*txt;

	txt = readfile(path);
	if (!txt)
	{
		ft_putstr_fd("Error.\n", 2);
		return (0);
	}
	fdf(txt);
	free(txt);
	system("leaks -q fdf");
	return (0);
}
