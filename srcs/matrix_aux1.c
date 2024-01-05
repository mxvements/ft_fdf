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

void	arrdbl_print_3x3(double **m)
{
	const int	x_dim = 3;
	const int	y_dim = 3;
	int			x;
	int			y;

	x = 0;
	write(1, "print array: \n", 14);
	while (x < x_dim)
	{
		y = 0;
		while (y < y_dim)
		{
			printf("%d, %d: %f\n", x, y, m[x][y]);
			y++;
		}
		x++;
	}
	write(1, "\n", 1);
}

void	arrdbl_mult_3x3(double **m1, double **m2, double **rslt)
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

double	**arrdbl_init(int x_dim, int y_dim, int nbr)
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
			return (arrdbl_free(arr, x), NULL);
		y = 0;
		while (y < y_dim)
		{
			if (x == y)
				arr[x][y] = nbr;
			else
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

	rslt = arrdbl_init(3, 3, 1);
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
	return (rslt);
}
