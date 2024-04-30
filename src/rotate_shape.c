/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:57:38 by eouhrich          #+#    #+#             */
/*   Updated: 2024/04/29 11:45:48 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d_point	rotatex_point(t_3d_point point, float angle)
{
	t_3d_point	rotated_point;
	float		sin_angle;
	float		cos_angle;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	rotated_point.x = point.x;
	rotated_point.y = point.y * cos_angle - point.z * sin_angle;
	rotated_point.z = point.y * sin_angle + point.z * cos_angle;
	rotated_point.color = point.color;
	return (rotated_point);
}

t_3d_point	rotatey_point(t_3d_point point, float angle)
{
	t_3d_point	rotated_point;
	float		sin_angle;
	float		cos_angle;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	rotated_point.x = point.x * cos_angle + point.z * sin_angle;
	rotated_point.y = point.y;
	rotated_point.z = -point.x * sin_angle + point.z * cos_angle;
	rotated_point.color = point.color;
	return (rotated_point);
}

t_3d_point	rotatez_point(t_3d_point point, float angle)
{
	t_3d_point	rotated_point;
	float		sin_angle;
	float		cos_angle;

	sin_angle = sin(angle);
	cos_angle = cos(angle);
	rotated_point.x = point.x * cos_angle - point.y * sin_angle;
	rotated_point.y = point.x * sin_angle + point.y * cos_angle;
	rotated_point.z = point.z;
	rotated_point.color = point.color;
	return (rotated_point);
}
