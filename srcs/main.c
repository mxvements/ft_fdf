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

void	printlst(t_dll **head)
{
	t_ptcont	*cntnt;
	t_dll		*ptnode;
	int			i;

	ptnode = *head;
	i = 0;
	while (ptnode)
	{
		cntnt = ptnode->content;
		write(1, "(", 1);
		ft_putnbr_fd(i, 1);
		write(1, ") ", 2);
		ft_putnbr_fd(cntnt->height, 1);
		write(1, "//", 2);
		ft_putnbr_fd(cntnt->color, 1);
		write(1, "\n", 1);
		i++;
		ptnode = ptnode->next;
	}
	return ;
}

t_dll	**initlst(void)
{
	t_dll	**ptlst;

	ptlst = (t_dll**)malloc(sizeof(t_dll*));
	if (!ptlst)
		return (NULL);
	*ptlst = NULL;
	return (ptlst);
}

void	map_build(t_map	*map, t_dll **lst)
{
	int			x;
	int	 		y;
	t_dll		*ptnode;
	t_ptcont	*ptcont;

	x = 0;
	ptnode = *lst;
	map->map = (t_pt **)malloc(sizeof(t_pt *) * map->x_dim);
	if (!map->map)
		return ; //free everything in stack
	while (x < map->x_dim)
	{
		map->map[x] = (t_pt*)malloc(sizeof(t_pt) * map->y_dim);
		if (!map->map[x])
			return ; //free everything in stack
		y = 0;
		while (y < map->y_dim)
		{
			if (ptnode)
			{
				ptcont = ptnode->content;
				(map->map[x][y]).xyz[0] = x;
				(map->map[x][y]).xyz[1] = y;
				(map->map[x][y]).xyz[2] = ptcont->height;
				(map->map[x][y]).color = ptcont->color;
				ptnode = ptnode->next;
			}
			y++;
		}
		x++;
	}
	//must check that the map is complete, at the end no nodes should be left
	if (ptnode)
		lst = lst_evalerror(lst);
	return ;
}

void	map_getdim(t_dll **lst, char *txt)
{
	t_map	map;

	map.y_dim = ft_strchr_count(txt, '\n');
	map.x_dim = (ft_dllsize(*lst) / map.y_dim);
	
	ft_putnbr_fd(map.x_dim, 1);
	write(1, " - ", 3);
	ft_putnbr_fd(map.y_dim, 1);
	write(1, "\n", 1);

	map_build(&map, lst);
	return ;
}

int main(void)
{
	char	*path = "./test_maps/ERR_simple_pyramid.fdf";
	char	*txt;
	t_dll	**ptlst;

	txt = readfile(path);
	if (!txt)
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	//get list of point info from txt
	ptlst = initlst();
	a_parse(txt, ptlst);
	printlst(ptlst);
	system("leaks -q fdf");

	//start buiding a map
	map_getdim(ptlst, txt);
	//must free map and all pts



	/*
	** TODO:
	** - must create a t_dll **ptlst to start parsing
	** - get matrix dimensions from txt
	** - put list info on matrix (and free list)
	** - update pt info with x and y from matrix
	*/
	if (ptlst)
	{
		ft_dllfree(ptlst);
		free(ptlst);
	}
	free(txt);
	return (0);
}