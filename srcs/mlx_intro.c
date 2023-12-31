/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_intro.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:57:13 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/31 22:43:49 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_pixel;
	int		line_length;
	int		endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int	dst;
	int		line_length;
	int 	bpp;
	
	line_length = data->line_length;
	bpp = data->bits_pixel;
	dst = (y * line_length + x * (bpp / 8));
	*((unsigned int*)(dst + data->addr)) = color;
}

//everytime a key is pressed this funct is called
//In linux we use KEYSYM in mac.. keycode?
int	handle_input(int keysym, t_data *data)
{
	if (keysym == XK_Escape) //Linux: XK_Escape mAC key 53
	{
		write(1, "(EXC)\n", 6);
		mlx_destroy_window(data->mlx, data->mlx_win);
		return (1);
	}
	printf("Key: (%d)\n", keysym);
	return (0);
}



int	main(void)
{
	t_data	data;
	int		color;
	int 	y;

	//stablish the connection with mlx
	data.mlx = mlx_init(); 
	if (!data.mlx)
		return (1);
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Wndw");
	
	// HOOKS
	/*
	* Note: On MacOS - Cocoa (AppKit) and OpenGL - version, minilibx has
	partial support of X11 events and doesn’t support X11 mask (x_mask
	argument of mlx_hook is useless, keep it at 0).
	* 
	*  HOOKING EVENT
	* 2 -> keydown
	* 17 -> on_destroy
	*/
	
	
	// Alias hooking functions, for expose event, key event, and mouse event
	//mlx_key_hook(data.mlx_win, handle_input, &data);
	

	
	
	
	data.img = mlx_new_image(data.mlx, WIDTH, WIDTH);
	data.addr = mlx_get_data_addr(data.img, &data.bits_pixel, &data.line_length,
								&data.endian);
	color = 0x00FF0000; //red
	y = 0;
	while (y < WIDTH)
	{
		my_mlx_pixel_put(&data, y, y, color);
		y++;
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img, 0, 0);
	

	
	mlx_loop(data.mlx);
	free(data.mlx);
	return (0);
}