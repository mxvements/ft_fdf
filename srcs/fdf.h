/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:40:54 by luciama2          #+#    #+#             */
/*   Updated: 2023/12/27 17:40:55 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <fcntl.h>

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include "automata.h"

# define WIDTH		500
# define HEIGHT		500
# define KEY_ESC    53

typedef struct s_point
{
	int	xyz[3]; //{x, y, z}
	int color;
}	t_pt;

typedef struct s_map
{
	int		x_dim;
	int		y_dim;
	t_pt	**map;
}	t_map;

#endif