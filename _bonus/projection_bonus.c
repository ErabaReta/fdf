/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 19:02:54 by eouhrich          #+#    #+#             */
/*   Updated: 2024/05/01 18:52:08 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_3d_point	turn_spheric(t_vars *vars, int i, int j)
{
	t_3d_point	point3d;
	float		r;
	float		alhpa;
	float		beta;

	r = (vars->shape_3d[i][j].z + ft_max(ft_max(vars->width, vars->height),
				vars->top_z)) * 0.75;
	alhpa = (((vars->shape_3d[i][j].x
					+ (vars->height / 2)) * 360) / vars->width) * (M_PI / 180);
	beta = (((vars->shape_3d[i][j].y
					+ (vars->height / 2)) * 180) / vars->height) * (M_PI / 180);
	point3d.x = r * sin(-beta) * cos(-alhpa);
	point3d.y = r * sin(-beta) * sin(-alhpa);
	point3d.z = r * cos(-beta);
	point3d.color = vars->shape_3d[i][j].color;
	return (point3d);
}

t_3d_point	get_coords(t_vars *vars, int i, int j)
{
	t_3d_point	point3d;

	point3d = vars->shape_3d[i][j];
	if (vars->coords_sestym == 's')
	{
		point3d = turn_spheric(vars, i, j);
	}
	point3d = rotatez_point(point3d, vars->zangle);
	point3d = rotatex_point(point3d, vars->xangle);
	point3d = rotatey_point(point3d, vars->yangle);
	point3d.color = vars->shape_3d[i][j].color;
	point3d.x += vars->xtranslation;
	point3d.y += vars->ytranslation;
	point3d.z += vars->ztranslation;
	return (point3d);
}

t_2d_point	perspective_projection(t_3d_point point3d, float fov)
{
	t_2d_point	point2d;
	float		x_proj;
	float		y_proj;

	if (point3d.z >= 0)
	{
		point2d.x = -1;
		point2d.y = -1;
		return (point2d);
	}
	x_proj = (point3d.x * -10) / point3d.z;
	y_proj = (point3d.y * -10) / point3d.z;
	point2d.x = x_proj * fov + WIN_WIDTH / 2 ;
	point2d.y = y_proj * fov + WIN_HEIGHT / 2;
	point2d.color = point3d.color;
	return (point2d);
}

t_2d_point	project_point(t_vars *vars, int i, int j)
{
	t_2d_point	point2d;
	t_3d_point	point3d;

	point3d = get_coords(vars, i, j);
	if (vars->projection == 'p')
		return (perspective_projection(point3d, vars->zoom));
	point2d.x = point3d.x * vars->zoom + WIN_WIDTH / 2;
	point2d.y = point3d.y * vars->zoom + WIN_HEIGHT / 2;
	point2d.color = point3d.color;
	return (point2d);
}
