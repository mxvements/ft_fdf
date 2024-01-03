/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_aux1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:30:57 by luciama2          #+#    #+#             */
/*   Updated: 2024/01/02 17:31:09 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	arrdbl_print_3x3(double m[3][3])
{
	const int	x_dim = 3;
	const int	y_dim = 3;
	int			x;
	int			y;

	x = 0;
	while (x < x_dim)
	{
		y = 0;
		while (y < y_dim)
		{
			printf("%f", m[x][y]);
			y++;
		}
		x++;
	}
	write(1, "\n", 1);
}

void	arrdbl_mult_3x3(double m1[3][3], double m2[3][3], double rslt[3][3])
{
	int		i;
	int		j;
	int		k;
	double	nbr;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			k = 0;
			nbr = 0;
			while (k < 3)
			{
				nbr += m1[i][k] * m2[k][j];
				k++;
			}
			rslt[i][j] = nbr;
			j++;
		}
		i++;
	}
}

void	arrdbl_free(double **arr, int x_dim)
{
	int	x;

	x = 0;
	while (x < x_dim)
	{
		free(arr[x]);
		arr[x] = NULL;
		x++;
	}
	free(arr);
}

double	**arrdbl_init(int x_dim, int y_dim)
{
	double	**arr;
	int		x;
	int		y;

	arr = (double**)malloc(sizeof(double*) * x_dim);
	if (!arr)
		return (NULL);
	x = 0;
	while (x < x_dim)
	{
		arr[x] = (double*)malloc(sizeof(double) * y_dim);
		if (!arr[x])
		{
			arrdbl_free(arr, x);
			return (NULL);
		}
		y = 0;
		while (y < y_dim)
		{
			arr[x][y] = 0;
			y++;
		}
		x++;
	}
	return (arr);
}

double	**arrdbl_cpy_3x3(double **arr)
{
	double	**rslt;
	int		x;
	int		y;

	rslt = arrdbl_init(3, 3);
	if (!rslt)
		return (NULL);
	x = 0;
	while (x < 3)
	{
		y = 0;
		while (y < 3)
		{
			rslt[x][y] = arr[x][y];
			y++;
		}
		x++;
	}
}
