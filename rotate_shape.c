/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_shape.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 17:57:38 by eouhrich          #+#    #+#             */
/*   Updated: 2024/04/28 17:57:39 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d_point rotateX_point(t_3d_point point, float angle)
{
    t_3d_point	rotatedPoint;
    float		sinAngle;
    float		cosAngle;

	sinAngle = sin(angle);
	cosAngle = cos(angle);
    rotatedPoint.x = point.x;
    rotatedPoint.y = point.y * cosAngle - point.z * sinAngle;
    rotatedPoint.z = point.y * sinAngle + point.z * cosAngle;
	rotatedPoint.color = point.color;
    return rotatedPoint;
}

t_3d_point rotateY_point(t_3d_point point, float angle)
{
    t_3d_point	rotatedPoint;
    float		sinAngle;
    float		cosAngle;

	sinAngle = sin(angle);
	cosAngle = cos(angle);
    rotatedPoint.x = point.x * cosAngle + point.z * sinAngle;
    rotatedPoint.y = point.y;
    rotatedPoint.z = -point.x * sinAngle + point.z * cosAngle;
	rotatedPoint.color = point.color;
    return rotatedPoint;
}

t_3d_point rotateZ_point(t_3d_point point, float angle)
{
    t_3d_point	rotatedPoint;
    float		sinAngle;
    float		cosAngle;

	sinAngle = sin(angle);
	cosAngle = cos(angle);
    rotatedPoint.x = point.x * cosAngle - point.y * sinAngle;
    rotatedPoint.y = point.x * sinAngle + point.y * cosAngle;
    rotatedPoint.z = point.z;
	rotatedPoint.color = point.color;
    return rotatedPoint;
}
