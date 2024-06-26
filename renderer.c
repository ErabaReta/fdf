/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:13:12 by eouhrich          #+#    #+#             */
/*   Updated: 2024/04/30 16:34:14 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	calc_color(int z1, int z2, int color1, int color2)
{
	if (z1 >= z2)
		return (color1);
	return (color2);
}

void	draw_lines(t_vars *vars, int i, int j)
{
	t_2d_point	point1;
	t_2d_point	point2;
	int			color;

	point1 = project_point(vars, i, j);
	if (i + 1 < vars->height)
	{
		point2 = project_point(vars, i + 1, j);
		color = calc_color(vars->shape_3d[i][j].z, vars->shape_3d[i + 1][j].z,
				vars->shape_3d[i][j].color, vars->shape_3d[i + 1][j].color);
		line_between_2points(vars, point1, point2, color);
	}
	if (j + 1 < vars->width)
	{
		point2 = project_point(vars, i, j + 1);
		color = calc_color(vars->shape_3d[i][j].z, vars->shape_3d[i][j + 1].z,
				vars->shape_3d[i][j].color, vars->shape_3d[i][j + 1].color);
		line_between_2points(vars, point1, point2, color);
	}
}

void	draw_map(t_vars *vars)
{
	int	i;
	int	j;
	int	end_i;
	int	end_j;

	i = 0;
	end_i = vars->height - 1;
	while (i <= end_i)
	{
		j = 0;
		end_j = vars->width - 1 ;
		while (j <= end_j)
			draw_lines(vars, ft_abs(i), ft_abs(j++));
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
}
