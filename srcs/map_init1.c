/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:20:49 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/23 10:20:51 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	map_size_x(char *txt)
{
	int			count;
	int			i;
	const char	*dict_m = "0123456789abcdefx,";
	const char	*dict_mm = "0123456789ABCDEFX,";

	i = -1;
	count = 0;
	while (txt[++i] != '\0')
	{
		if ((ft_strchr(dict_m, txt[i]) != 0 || ft_strchr(dict_mm, txt[i]) != 0)
			&& (txt[i + 1] == ' ' || txt[i + 1] == '\0'
				|| txt[i + 1] == '\n'))
			count++;
	}
	return (count);
}

static char	*map_gnljoin(char *gnl, char *txt, int xy[2])
{
	static int	x0;
	char		*tmp;

	if (!txt)
	{
		x0 = map_size_x(gnl);
		return (gnl);
	}
	if (xy[0] != x0 || xy[0] == 0)
	{
		free(txt);
		free(gnl);
		return (NULL);
	}
	tmp = ft_strjoin(txt, gnl);
	free(txt);
	free(gnl);
	return (tmp);
}

char	*map_read_size(char *path, t_map *map)
{
	char	*txt;
	char	*gnl;
	int		fd;
	int		xy[2];

	if (!(*path))
		return (NULL);
	txt = NULL;
	fd = open(path, O_RDONLY);
	xy[1] = 0;
	while (1)
	{
		gnl = get_next_line(fd);
		if (gnl == NULL)
			break ;
		xy[1]++;
		xy[0] = map_size_x(gnl);
		txt = map_gnljoin(gnl, txt, xy);
		if (!txt)
			return (NULL);
	}
	close(fd);
	map->x_dim = xy[0];
	map->y_dim = xy[1];
	return (txt);
}

static void	fdf_hooks(t_map *map)
{
	mlx_key_hook(map->mlx_data.mlx_win, fdf_key_input, map);
	mlx_mouse_hook(map->mlx_data.mlx_win, fdf_mousedown_input, map);
	mlx_hook(map->mlx_data.mlx_win, 6, 0, fdf_mousemove_input, map);
	mlx_hook(map->mlx_data.mlx_win, 17, 0, fdf_handle_destroy, map);
}

void	fdf(char *path)
{
	char	*txt;
	t_map	*map;

	map = (t_map *)map_init();
	if (!map)
		return ;
	txt = map_read_size(path, map);
	if (!txt)
	{
		write(1, ANSICOLOR_RED, 6);
		ft_putstr_fd("Error.\n", 2);
		write(1, ANSICOLOR_RESET, 5);
		return (free(map));
	}
	map = map_build(txt, map);
	free(txt);
	if (!map)
		return ;
	fdf_hooks(map);
	mlx_loop((map->mlx_data).mlx);
	map_free_mlx(map);
	map = map_free(map);
	return ;
}
