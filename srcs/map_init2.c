/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:27:32 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/31 23:39:43 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_show_menu(void)
{
	write(1, ANSICOLOR_CYAN, 6);
	ft_putstr_fd("*************** fdf ***************\n", 1);
	ft_putstr_fd("Press (ESC) to close window\n", 1);
	ft_putstr_fd("Press (r) to rotate (WIP)\n", 1);
	ft_putstr_fd("Press (s) to scale (WIP)\n", 1);
	ft_putstr_fd("Press (t) to translate (WIP)\n", 1);
	write(1, ANSICOLOR_RESET, 5);
}

int	fdf_handle_input(int keysym, t_mlx *mlx_data)
{
	write(1, ANSICOLOR_GREEN, 6);
	if (keysym == XK_Escape)
	{
		write(1, "(EXC)\n", 6);
		mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
		write(1, ANSICOLOR_RESET, 5);
		return (1);
	}
	printf("Key: (%d)\n", keysym);
	write(1, ANSICOLOR_RESET, 5);
	return (0);
}
void	fdf_isometric(t_map *map)
{

}

t_map	*map_initmlx(t_map *map)
{	
	void	*mlx;
	void	*mlx_win;
	int		key_input;
	
	map->mlx_data.mlx = mlx_init();
	mlx = map->mlx_data.mlx;
	if (!mlx)
		return (NULL);
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "fdf");
	map->mlx_data.mlx_win = mlx_win;
	fdf_show_menu();
	key_input = mlx_key_hook(mlx_win, fdf_handle_input, &map->mlx_data);
	if (key_input == 1)
		return (NULL);
	map->mlx_data.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	map->mlx_data.img_addr = mlx_get_data_addr(
								(map->mlx_data).img,
								&(map->mlx_data).bpp,
								&(map->mlx_data).line_len,
								&(map->mlx_data).endian);
		
	//WRITE PIXELS -> fdf_isometric(map)
	return (map);
}
