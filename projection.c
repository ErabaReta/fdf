/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:02:54 by eouhrich          #+#    #+#             */
/*   Updated: 2024/05/01 18:52:08 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d_point	get_coords(t_vars *vars, int i, int j)
{
	t_3d_point	point3d;

	point3d = vars->shape_3d[i][j];
	point3d = rotatez_point(point3d, vars->zangle);
	point3d = rotatex_point(point3d, vars->xangle);
	point3d = rotatey_point(point3d, vars->yangle);
	point3d.color = vars->shape_3d[i][j].color;
	return (point3d);
}

t_2d_point	project_point(t_vars *vars, int i, int j)
{
	t_2d_point	point2d;
	t_3d_point	point3d;

	point3d = get_coords(vars, i, j);
	point2d.x = point3d.x * vars->zoom + WIN_WIDTH / 2;
	point2d.y = point3d.y * vars->zoom + WIN_HEIGHT / 2;
	point2d.color = point3d.color;
	return (point2d);
}
