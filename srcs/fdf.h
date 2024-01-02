/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmmielgo <lmmielgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:40:54 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/02 10:30:01 by lmmielgo         ###   ########.fr       */
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
	int color;
}	t_pt;

typedef struct s_map
{
	int		x_dim;
	int		y_dim;
	int		offset_pixel;
	
	t_pt	**map;
	t_mlx	mlx_data;
}	t_map;

//pt functions
void	pt_print(t_pt **ptarr, int xdim, int ydim);
//MLX
t_map	*map_initmlx(t_map *map);
//map  init
void 	*map_evalerror(t_map *map);
t_dll	*map_getptinfo(t_dll *ptnode, t_map *map, int x, int y); //could be static
t_map	*map_initdptmap(t_map	*map, t_dll **lst);
t_map	*map_initsize(t_dll **ptlst, char *txt, t_map *map);
t_map	*map_init(t_dll **lst, char *txt);

#endif