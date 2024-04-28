#include "fdf.h"

void	line_between_2points(t_vars	*vars, t_2d_point point1, t_2d_point point2, int color)
{
	int	x;
	int	y;

	if ((point1.x == -1 && point1.y == -1) || (point2.x == -1 && point2.y == -1))
		return ;
	if ((point2.y - point1.y) != 0)
	{
		y = ft_max(ft_min(point1.y, point2.y), 0);
		while (y <= ft_max(point1.y, point2.y) && y < WINDOW_HEIGHT)
		{
			x = (((y - point1.y) * (point2.x - point1.x)) / (point2.y - point1.y) ) + point1.x;
			my_mlx_pixel_put(&(vars->data), x, y, color);
			y++;
		}
	} if (point2.x - point1.x != 0)
	{
		x = ft_max(ft_min(point1.x, point2.x), 0);
		while (x <= ft_max(point1.x, point2.x) && x < WINDOW_WIDTH)
		{
			y = (((point2.y - point1.y) * (x - point1.x )) / (point2.x - point1.x)) + point1.y;
			my_mlx_pixel_put(&(vars->data), x, y, color);
			x++;
		}
	}
}

int calc_color(int z1, int z2, int color1, int color2)
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
		color = calc_color(vars->shape_3d[i][j].z, vars->shape_3d[i + 1][j].z, vars->shape_3d[i][j].color, vars->shape_3d[i + 1][j].color);
		line_between_2points(vars, point1, point2, color);
	}
	if (j + 1 < vars->width)
	{
		point2 = project_point(vars, i ,j + 1);
		color = calc_color(vars->shape_3d[i][j].z, vars->shape_3d[i][j + 1].z, vars->shape_3d[i][j].color, vars->shape_3d[i][j + 1].color);
		line_between_2points(vars, point1, point2, color);
	}
	if ((j + 1 == vars->width) && vars->coords_sestym == 's')
	{
		point2 = project_point(vars, i ,0);
		color = calc_color(vars->shape_3d[i][j].z, vars->shape_3d[i][0].z, vars->shape_3d[i][j].color, vars->shape_3d[i][0].color);
		line_between_2points(vars, point1, point2, color);
	}
}

// void draw_scope(t_vars *vars)
// {
// 	int i= 0;

// 	while (i < WINDOW_HEIGHT)
// 	{
// 		my_mlx_pixel_put(&(vars->data), WINDOW_HEIGHT / 2 , i, 0xffffff);
// 		my_mlx_pixel_put(&(vars->data), i , WINDOW_HEIGHT / 2, 0xffffff);
// 		i++;
// 	}
// }

void	rendering_direction(int *i, int *end_i)
{
	t_vars	*vars;

	vars = get_vars();
	if (get_coords(vars, 0, 0).z <= get_coords(vars, vars->height - 1, 0).z)
	{
		*i = 0;
		*end_i = vars->height - 1;
	}
	else
	{
		*i = -(vars->height - 1);
		*end_i = 0;
	}

}

void	draw_map(t_vars *vars)
{
	int	i;
	int	j;
	int	end_i;
	int	end_j;

	rendering_direction(&i, &end_i);
	while (i <= end_i)
	{
		if (get_coords(vars, 0, 0).z < get_coords(vars, 0, vars->width - 1).z)
		{
			j = 0;
			end_j = vars->width - 1 ;
		}
		else
		{
			j = -(vars->width - 1);
			end_j = 0;
		}
		while (j <= end_j)
			draw_lines(vars, ft_abs(i), ft_abs(j++));
		i++;
	}
	// draw_scope(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
}