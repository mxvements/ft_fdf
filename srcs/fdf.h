/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:40:54 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/05 22:44:07 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

//MAC
//# include <mlx.h>
//# include "./fdf_mac_keys.h"

//LINUX 
# include "../mlx_linux/mlx.h"
# include "./fdf_linux_keys.h"

# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "automata.h"

# define ANSICOLOR_CYAN		"\x1b[36m"
# define ANSICOLOR_RED		"\x1b[31m"
# define ANSICOLOR_GREEN	"\x1b[32m"
# define ANSICOLOR_YELLOW	"\x1b[33m"
# define ANSICOLOR_BLUE		"\x1b[34m"
# define ANSICOLOR_MAGENTA	"\x1b[35m"
# define ANSICOLOR_RESET	"\x1b[0m"

# define WIDTH				1280
# define HEIGHT				720
# define PADDING			100

# if WIDTH >= HEIGHT
#	define MIN_SIDE			HEIGHT
# else
#	define MIN_SIDE			WIDTH
# endif

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*img_addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx;

typedef struct s_point
{
	int	xyz[3]; //{x, y, z}
	int	vw_xyz[3];
	int	pixel_xy[2];
	int color;
}	t_pt;

typedef struct s_view
{
	double	scale_f; //DO CHECK VIEW, scala cannot be zero
	double	rotate_rads_z;
	double	rotate_rads_y;
	double	rotate_rads_x;
	double	move_d;
	double	**view; //array of 3x3
}	t_view;

typedef struct s_map
{
	int		x_dim;
	int		y_dim;
	t_view	*vw;
	t_pt	**map; //double array of points of x_dim and y_dim of map
	t_mlx	mlx_data;
}	t_map;

//pt/
void	pt_print(t_pt **ptarr, int xdim, int ydim);
void	pt_transform(t_pt *pt, t_view *vw);
//arr functions
void	arrdbl_print_3x3(double **m);
void	arrdbl_mult_3x3(double **m1, double **m2, double **rslt);
void	arrdbl_free(double **arr, int x_dim);
double	**arrdbl_init(int x_dim, int y_dim, int nbr);
double	**arrdbl_cpy_3x3(double **arr);
//view funct
void	view_rot_z(t_view *vw);
void	view_rot_y(t_view *vw);
void	view_rot_x(t_view *vw);
void	view_scale(t_view *vw);
void	view_translate(t_view *vw);
void	view_rotate(t_view *vw);
void	view_isometric(t_view *vw);
//fdf aux functions
void	fdf_show_menu(void);
int		fdf_handle_input(int keysym, t_mlx *mlx_data);
void	fdf_pixelput(t_mlx *mlx, int x, int y, int color);
void	fdf_lineBresenham(int x1, int y1, int x2, int y2);
//MLX
t_map	*map_mlx(t_map *map);
//map  init
void 	*map_evalerror(t_map *map, int x);
t_dll	*map_getptinfo(t_dll *ptnode, t_map *map, int x, int y); //could be static
t_map	*map_ptmap(t_map *map, t_dll **lst);
t_map	*map_pixelptmap(t_map *map);
t_map	*map_viewptmap(t_map *map);
t_map	*map_view(t_map *map);
t_map	*map_size(t_dll **ptlst, char *txt, t_map *map);
t_map	*map_init(t_dll **lst, char *txt);

#endif