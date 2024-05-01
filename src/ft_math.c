/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:52:43 by eouhrich          #+#    #+#             */
/*   Updated: 2024/05/01 18:52:08 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int nbr)
{
	return (((nbr >= 0) - (nbr < 0)) * nbr);
}

float	ft_min(float nbr1, float nbr2)
{
	if (nbr1 >= nbr2)
		return (nbr2);
	return (nbr1);
}

float	ft_max(float nbr1, float nbr2)
{
	if (nbr1 >= nbr2)
		return (nbr1);
	return (nbr2);
}

void	line_between_2points(t_vars	*vars, t_2d_point point1,
				t_2d_point point2, int color)
{
	int	x;
	int	y;

	if ((point1.x == -1 && point1.y == -1)
		|| (point2.x == -1 && point2.y == -1))
		return ;
	y = ft_max(ft_min(point1.y, point2.y), 0);
	while ((point2.y - point1.y) != 0
		&& y <= ft_max(point1.y, point2.y) && y < WIN_HEIGHT)
	{
		x = (((y - point1.y) * (point2.x - point1.x))
				/ (point2.y - point1.y)) + point1.x;
		my_mlx_pixel_put(&(vars->data), x, y++, color);
	}
	x = ft_max(ft_min(point1.x, point2.x), 0);
	while ((point2.x - point1.x) != 0
		&& x <= ft_max(point1.x, point2.x) && x < WIN_WIDTH)
	{
		y = (((point2.y - point1.y) * (x - point1.x))
				/ (point2.x - point1.x)) + point1.y;
		my_mlx_pixel_put(&(vars->data), x++, y, color);
	}
}
