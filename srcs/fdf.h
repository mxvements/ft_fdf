/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:40:54 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/11 23:41:27 by lmmielgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
//MAC
# include <mlx.h>
# include "./fdf_mac_keys.h"
//LINUX 
//# include "../mlx_linux/mlx.h"
//# include "./fdf_linux_keys.h"
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# define ANSICOLOR_GRAY		"\x1b[30m"
# define ANSICOLOR_RED		"\x1b[31m"
# define ANSICOLOR_GREEN	"\x1b[32m"
# define ANSICOLOR_YELLOW	"\x1b[33m"
# define ANSICOLOR_BLUE		"\x1b[34m"
# define ANSICOLOR_MAGENTA	"\x1b[35m"
# define ANSICOLOR_CYAN		"\x1b[36m"
# define ANSICOLOR_RESET	"\x1b[0m"
# define WIDTH				1280
# define HEIGHT				720
# define SCALE				15
# define ZSCALE				5

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
	int	xyz[3];
	int	vw_xyz[3];
	int	px_xy[2];
	int	color;
}	t_pt;

typedef struct s_view
{
	double	scale_f;
	double	rot_rad_z;
	double	rot_rad_y;
	double	rot_rad_x;
	double	move_d_y;
	double	move_d_x;
	double	**view;
}	t_view;

typedef struct s_keyin
{
	int		*keysym;
	int		key_tr;
	int		key_ax;
	double	key_nbr;
	double	key_sign;
	int		mouse_xy[2];
	int		mouse_flag;
}	t_keyin;

typedef struct s_map
{
	int		x_dim;
	int		y_dim;
	t_pt	**map;
	t_view	*vw;
	t_keyin	*keys;
	t_mlx	mlx_data;
}	t_map;
/* ************************************************************************** */
/*                                    pt                                      */
/* ************************************************************************** */
//void	pt_print(t_pt **ptarr, int xdim, int ydim);
void	pt_rotate(t_pt *pt, t_view *vw);
/* ************************************************************************** */
/*                                   arr                                      */
/* ************************************************************************** */
void	arrdbl_print_3x3(double **m);
void	arrdbl_mult_3x3(double **m1, double **m2, double **rslt);
void	arrdbl_free(double **arr, int x_dim);
double	**arrdbl_init(int x_dim, int y_dim, int nbr);
double	**arrdbl_cpy_3x3(double **arr);
/* ************************************************************************** */
/*                                    vw                                      */
/* ************************************************************************** */
void	view_rot_z(t_view *vw);
void	view_rot_y(t_view *vw);
void	view_rot_x(t_view *vw);
void	view_scale(t_view *vw);
void	view_rotate(t_view *vw);
void	view_isometric(t_map *map);
void	view_plan(t_map	*map);
/* ************************************************************************** */
/*                               map change                                   */
/* ************************************************************************** */
int		map_escape(t_map *map);
int		map_updatevw(t_map *map);
int		map_change(t_map *map);
/* ************************************************************************** */
/*                                   mlx                                      */
/* ************************************************************************** */
t_map	*map_mlx(t_map *map);
void	map_printview(t_map *map);
/* ************************************************************************** */
/*                               init view                                    */
/* ************************************************************************** */
void	*map_free(t_map *map);
void	*map_free_keystruct(t_keyin *keys);
void	*map_free_vwstruct(t_view *vw);
void	*map_free_ptmap(t_map *map, int x);
void	map_free_mlx(t_map *map);
void	*map_evalerror_ptmap(t_map *map, int y);
t_map	*map_pixelptmap(t_map *map);
t_map	*map_viewptmap(t_map *map);
t_map	*map_view(t_map *map);
t_map	*map_build(char *txt, t_map *map);
char	*map_read_size(char *path, t_map *map);
void	*map_init(void);
void	fdf(char *path);
/* ************************************************************************** */
/*                        fdf aux (hooks & menu)                              */
/* ************************************************************************** */
void	fdf_show_menu(void);
void	fdf_show_transformation(t_keyin *keys);
int		fdf_handle_input_rst(t_map *map);
int		fdf_handle_input_xyz(t_map *map);
int		fdf_handle_input_nbr(t_map *map);
int		fdf_handle_input_sign(t_map *map);
int		fdf_handle_input_zoom(t_map *map);
int		fdf_handle_input_pan(t_map *map);
int		fdf_handle_input_height(t_map *map);
int		fdf_handle_input_reset(t_map *map);
int		fdf_hanlde_input_enter(t_map *map);
int		fdf_handle_destroy(t_map *map);
int		fdf_key_input(int keysym, t_map *map);
int		fdf_mousedown_input(int button, int x, int y, t_map *map);
int		fdf_mousemove_input(int x, int y, t_map *map);
t_map	*fdf_keystruct_init(t_map *map);
void	fdf_keystruct_reset(t_keyin *keys);
/* ************************************************************************** */
/*                           colors and lines                                 */
/* ************************************************************************** */
int		*fdf_putcolor_wrapper(t_pt *pt1, t_pt *pt2, const int dx, const int dy);
t_map	*fdf_putlines(t_map *map, int x, int y);
void	fdf_pxput(t_mlx *mlx, int x, int y, int color);
/* ************************************************************************** */
/*                                  parse                                     */
/* ************************************************************************** */
t_map	*txt_parse(char *txt, t_map *map);

#endif