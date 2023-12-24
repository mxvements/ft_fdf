/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 16:58:27 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/24 19:50:32 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_linux/mlx.h"
#include "../mlx_linux/mlx_int.h"
#include "../libft/libft.h"
#include "../gnl/get_next_line.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_p_pixel;
	int		line_length;
	int		endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	
	/* The pixels are basically ints
	+  ints are usually 4 bytes
	*  this can differ if we are dealing with a small endian
	*  (which means we most likely are on a remote display and only have
	*  8 bit colors).
	* A big-endian system stores the most significant byte of a word at the
	* smallest memory address and the least significant byte at the largest.
	* A little-endian system, in contrast, stores the least-significant byte at
	* the smallest address
	* */
	dst = data->addr + ((y * data->line_length) + (x * (data->bits_p_pixel / 8)));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		color;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_p_pixel, &img.line_length,
								&img.endian);
	color = 0x00FF0000; //red
	my_mlx_pixel_put(&img, 5, 5, color);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}

