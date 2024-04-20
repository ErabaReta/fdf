#include "fdf.h"

t_3d_point rotateX_point(t_3d_point point, float angle)
{
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    t_3d_point rotatedPoint;
    rotatedPoint.x = point.x;
    rotatedPoint.y = point.y * cosAngle - point.z * sinAngle;
    rotatedPoint.z = point.y * sinAngle + point.z * cosAngle;
	rotatedPoint.color = point.color;
    return rotatedPoint;
}

t_3d_point rotateY_point(t_3d_point point, float angle)
{
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    t_3d_point rotatedPoint;
    rotatedPoint.x = point.x * cosAngle + point.z * sinAngle;
    rotatedPoint.y = point.y;
    rotatedPoint.z = -point.x * sinAngle + point.z * cosAngle;
	rotatedPoint.color = point.color;
    return rotatedPoint;
}

t_3d_point rotateZ_point(t_3d_point point, float angle)
{
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    t_3d_point rotatedPoint;
    rotatedPoint.x = point.x * cosAngle - point.y * sinAngle;
    rotatedPoint.y = point.x * sinAngle + point.y * cosAngle;
    rotatedPoint.z = point.z;
	rotatedPoint.color = point.color;
    return rotatedPoint;
}

void	rotate_shape(t_vars *vars, float angle, char axis)
{

	int i;
	int	j;
	t_3d_point point3d;

	point3d = vars->shape_3d[(vars->height) / 2][(vars->width) / 2];
	i= 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			vars->shape_3d[i][j].x -= point3d.x;
			vars->shape_3d[i][j].y -= point3d.y;
			vars->shape_3d[i][j].z -= point3d.z;

			if (axis == 'x')
				vars->shape_3d[i][j] = rotateX_point(vars->shape_3d[i][j], angle);//
			else if (axis == 'y')
				vars->shape_3d[i][j] = rotateY_point(vars->shape_3d[i][j], angle);//
			else if (axis == 'z')
				vars->shape_3d[i][j] = rotateZ_point(vars->shape_3d[i][j], angle);//


			vars->shape_3d[i][j].x += point3d.x;
			vars->shape_3d[i][j].y += point3d.y;
			vars->shape_3d[i][j].z += point3d.z;
			j++;
		}
		i++;
	}
}