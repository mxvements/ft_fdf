/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 16:58:27 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/30 23:11:01 by luciama2         ###   ########.fr       */
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

int main(void)
{
	char	*path = "./test_maps/ERR_simple_pyramid.fdf";
	char	*txt;
	t_dll	**ptlst;
	t_map	*map;

	txt = readfile(path);
	if (!txt)
	{
		ft_putstr_fd("Error.\n", 2);
		return (0);
	}
	//get list of point info from txt
	ptlst = initlst();
	a_parse(txt, ptlst); //updates ptlst with all ptinfo on the file
	//printlst(ptlst);
	
	//MAP init
	map = map_init(ptlst, txt);

	free(txt);
	system("leaks -q fdf");
	return (0);
}
