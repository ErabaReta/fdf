#include "fdf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;
	int offset;

	if (y >= WINDOW_HEIGHT || x >= WINDOW_WIDTH || x < 0 || y < 0)
		return ;
	offset = y * data->line_length + x * (data->bits_per_pixel / 8);
	dst = data->addr + offset;
	*(unsigned int*)dst = color;
}

// void	draw_mostatil(t_img_data *img, int l3ard, int tol, t_point point)
// {
// 	int i = 0;
// 	int j = 0;

// 	while (i < l3ard)
// 	{
// 		j = 0;
// 		while (j < tol)
// 		{
// 			printf("writed a pixel to x == %d   y == %d\n", point.x + j, point.y + i );
// 			my_mlx_pixel_put(img, point.x + j, point.y + i, 0x00FF0000);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	draw_mo3ayan(t_img_data *img, int l3ard, int tol, t_point point)
// {
// 	int i =0;
// 	int j =0;

// 	(void)tol;
// 	while (i < l3ard)
// 	{
// 		j = 0;
// 		while (j < i)
// 		{
// 			my_mlx_pixel_put(img, point.x + j, point.y + i, 0x00FF0000);
// 			j++;
// 		}
// 		j = 0;
// 		while (j < i)
// 		{
// 			my_mlx_pixel_put(img, point.x - j, point.y + i, 0x00FF0000);
// 			j++;
// 		}
// 		i++;
// 	}
// 	int k = 0;
// 	while (i < 2 * l3ard)
// 	{
// 		j = l3ard - k;
// 		while (j >= 0)
// 		{
// 			my_mlx_pixel_put(img, point.x + j, point.y + i, 0x00FF0000);
// 			j--;
// 		}
// 		j = l3ard - k;
// 		while (j >= 0)
// 		{
// 			my_mlx_pixel_put(img, point.x - j, point.y + i, 0x00FF0000);
// 			j--;
// 		}
// 		k++;
// 		i++;
// 	}

// }

void	draw_circle(t_img_data *img, int cho3a3, t_2d_point point)
{
	int i = point.y - cho3a3;
	int j;

	// while (i < 299)
	// {
	// 	j = 0;
	// 	while (j < 299)
	// 	{
	// 		if (  (ft_power(ft_abs(j - point.x), 2) + ft_power(ft_abs(i - point.y), 2))       == ft_power(cho3a3, 2))
	// 		my_mlx_pixel_put(img, j, i, 0x00FF0000);
	// 		j++;
	// 	}
	// 	i++;
	// }
	while (i < point.y + cho3a3)
	{
		j = point.x - cho3a3;
		while (j < point.x + cho3a3)
		{
			if (calc_dist(j, i, point) <= cho3a3)
			{
				// printf("pixeled the point x ==%d  | y == %d | with dist == %d\n", j, i, calc_dist(j, i, point));
				my_mlx_pixel_put(img, j, i, 0x00FFFFFF);
			}
			j++;
		}
		i++;
	}
}

// int	draw(int button, int x, int y, void *ptr)
// {
// 	t_2d_point point;

// 	point.x = x;
// 	point.y = y;

// 	(void)button;
// 	t_vars *vars = (t_vars *)ptr;
// 	draw_circle(&(vars->data), 10, point);
// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
// 	return (0);
// }

t_3d_point rotateX_point(t_3d_point point, float angle) {
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    t_3d_point rotatedPoint;
    rotatedPoint.x = point.x;
    rotatedPoint.y = point.y * cosAngle - point.z * sinAngle;
    rotatedPoint.z = point.y * sinAngle + point.z * cosAngle;
    return rotatedPoint;
}

t_3d_point rotateY_point(t_3d_point point, float angle) {
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    t_3d_point rotatedPoint;
    rotatedPoint.x = point.x * cosAngle + point.z * sinAngle;
    rotatedPoint.y = point.y;
    rotatedPoint.z = -point.x * sinAngle + point.z * cosAngle;
    return rotatedPoint;
}

t_3d_point rotateZ_point(t_3d_point point, float angle) {
    float sinAngle = sin(angle);
    float cosAngle = cos(angle);
    t_3d_point rotatedPoint;
    rotatedPoint.x = point.x * cosAngle - point.y * sinAngle;
    rotatedPoint.y = point.x * sinAngle + point.y * cosAngle;
    rotatedPoint.z = point.z;
    return rotatedPoint;
}

void	rotate_shape(t_vars *vars, float xangle, char axis)
{
	t_3d_point	point3d;
	int i;
	int	j;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			point3d.x = vars->shape_3d[i][j].value[0][0] - vars->shape_3d[(vars->height) / 2][(vars->width) / 2].value[0][0];
			point3d.y = vars->shape_3d[i][j].value[1][0] - vars->shape_3d[(vars->height) / 2][(vars->width) / 2].value[1][0];
			point3d.z = vars->shape_3d[i][j].value[2][0] - vars->shape_3d[(vars->height) / 2][(vars->width) / 2].value[2][0];

			if (axis == 'x')
				point3d = rotateX_point(point3d, xangle);//
			else if (axis == 'y')
				point3d = rotateY_point(point3d, xangle);//
			else if (axis == 'z')
				point3d = rotateZ_point(point3d, xangle);//


			vars->shape_3d[i][j].value[0][0] = point3d.x + vars->shape_3d[(vars->height) / 2][(vars->width) / 2].value[0][0];
			vars->shape_3d[i][j].value[1][0] = point3d.y + vars->shape_3d[(vars->height) / 2][(vars->width) / 2].value[1][0];
			vars->shape_3d[i][j].value[2][0] = point3d.z + vars->shape_3d[(vars->height) / 2][(vars->width) / 2].value[2][0];
			j++;
		}
		i++;
	}
}

void clear_image(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(&(vars->data), j, i, 0x00);
			j++;
		}
		i++;
	}
	// mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
}

void	translate_shape(t_vars *vars, int distence, char axis)
{
	int i;
	int	j;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			if (axis == 'x')
				vars->shape_3d[i][j].value[0][0] += distence;
			else if (axis == 'y')
				vars->shape_3d[i][j].value[1][0] += distence;
			else if (axis == 'z')
				vars->shape_3d[i][j].value[2][0] += distence;
			j++;
		}
		i++;
	}
}
 int	d = 1;////////////////////////////////////////////

int	handle_keys(int keycode, t_vars *vars)
{	
	printf("KEYCODE %d\n", keycode);//
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if ( keycode == Q)
	{
		rotate_shape(vars, ROTATION_ANGLE * (M_PI / 180), 'x');
	}
	else if ( keycode == W)
	{
		rotate_shape(vars, -ROTATION_ANGLE * (M_PI / 180), 'x');
	}
	else if ( keycode == A)
	{
		rotate_shape(vars, 2 * (M_PI / 180), 'y');
	}
	else if ( keycode == S)
	{
		rotate_shape(vars, -ROTATION_ANGLE * (M_PI / 180), 'y');
	}
		else if ( keycode == Z)
	{
		rotate_shape(vars, ROTATION_ANGLE * (M_PI / 180), 'z');
	}
		else if ( keycode == X)
	{
		rotate_shape(vars, -ROTATION_ANGLE * (M_PI / 180), 'z');
	}
		else if ( keycode == E)
	{
		translate_shape(vars, TRANSLATION_DISTENCE, 'x');
	}
		else if ( keycode == R)
	{
		translate_shape(vars, -TRANSLATION_DISTENCE, 'x');
	}
		else if ( keycode == D)
	{
		translate_shape(vars, TRANSLATION_DISTENCE, 'y');
	}
		else if ( keycode == F)
	{
		translate_shape(vars, -TRANSLATION_DISTENCE, 'y');
	}
		else if ( keycode == C)
	{
		translate_shape(vars, TRANSLATION_DISTENCE, 'z');
	}
		else if ( keycode == V)
	{
		translate_shape(vars, -TRANSLATION_DISTENCE, 'z');
	}
		else if (keycode == UP_ARROW)
	{
		d += 1;
	}
		else if (keycode == DOWN_ARROW)
	{
		d -= 1;
	}
	else
	{
		return (0);
	}
	if (d == 0)
		d+= 1;
	clear_image(vars);
	draw_map(vars);
	return (0);
}
// 13 == w
// 1 == s
// 0 == a

// 2 == d

// Define viewpoint
// t_3d_point viewpoint = {0, 0, 0};


// Function to project a 3D point to a 2D point
t_2d_point project_point(t_3d_point point3d) {

// Define projection matrix (simple perspective projection)
float projection_matrix[3][3] = {
    {d, 0, 0},
    {0, d, 0},
    {0, 0, 1}
};
	t_2d_point	point2d;
	// resolving the mirror porblem
	if (point3d.z >= 0)
	{
		point2d.x = -1;
		point2d.y = -1;
		return point2d;
	}
    // Apply projection
    float x_proj = point3d.x * projection_matrix[0][0] /*+ point3d.y * projection_matrix[1][0] + point3d.z * projection_matrix[2][0]*/;
    float y_proj = /*point3d.x * projection_matrix[0][1] +*/ point3d.y * projection_matrix[1][1]  /*+point3d.z * projection_matrix[2][1]*/;
    float z_proj = /*point3d.x * projection_matrix[0][2] + point3d.y * projection_matrix[1][2] +*/ point3d.z * projection_matrix[2][2];

    // Normalize coordinates
	if(z_proj != 0)
	{
	    x_proj /= z_proj;
    	y_proj /= z_proj;
	}

    // Create 2D point
    point2d.x = x_proj * 100 + 150;
	point2d.y = y_proj * 100 + 150;
    return point2d;
}

void	shape_3d_to_2d(t_vars	*vars)
{
	t_2d_point	point2d;
	t_3d_point	point3d;
	int 		i;
	int			j;

	vars->shape_2d = (t_matrix **)malloc(sizeof(t_matrix *) * (vars->height));
	i = 0;
	while (i < vars->height)
	{
		vars->shape_2d[i] = (t_matrix *)malloc(sizeof(t_matrix) * (vars->width));
		i++;
	}
	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			//The general equation of a sphere is: (x - a)² + (y - b)² + (z - c)² = r²
			//equation of plane is : a(x  - x0) + b(y - y0) + c(z - z0) = 0
			point3d.x = vars->shape_3d[i][j].value[0][0] - 20;
			point3d.y = vars->shape_3d[i][j].value[1][0]  - 20;
			point3d.z = (vars->shape_3d[i][j].value[2][0]) - 20;
			point2d = project_point(point3d);
			printf("the 3d point x = %f , y = %f ,  z = %f turn into 2d point x = %d ,  y = %d \n", point3d.x, point3d.y, point3d.z, point2d.x, point2d.y);
			(vars->shape_2d[i][j]).value = new_value(point2d.x, point2d.y, 0, 2);////!
			j++;
		}
		i++;
	}
}

int	ft_min(int nbr1, int nbr2)
{
	if (nbr1 >= nbr2)
		return (nbr2);
	return (nbr1);
}

int	ft_max(int nbr1, int nbr2)
{
	if (nbr1 >= nbr2)
		return (nbr1);
	return (nbr2);
}

void	line_between_2points(t_vars	*vars, t_2d_point point1, t_2d_point point2)
{
	int	x;
	int	y;

	if (point1.x == -1 || point2.x == -1 || point1.y == -1 || point2.y == -1)
		return ;
	if ((point2.y - point1.y) != 0)
	{
		y = ft_min(point1.y, point2.y);
		while (y < 0)
			y++;
		while (y <= ft_max(point1.y, point2.y) && y < WINDOW_HEIGHT)
		{
			// (y -y1) =[(y2 - y1) / (x2 - x1)] (x - x1) 
			x = (((y - point1.y) * (point2.x - point1.x)) / (point2.y - point1.y) ) + point1.x;
			my_mlx_pixel_put(&(vars->data), x, y, 0x00FFFFFF);
			y++;
		}
	} if (point2.x - point1.x != 0)
	{
		x = ft_min(point1.x, point2.x);
		while (x < 0)
			x++;
		while (x <= ft_max(point1.x, point2.x) && x < WINDOW_WIDTH)
		{
			// if (calc_dist(x, y, point1) + calc_dist(x, y, point2) == calc_dist(point1.x, point1.y, point2))  
			// (y -y1) =[(y2 - y1) / (x2 - x1)] (x - x1) 
			y = (((point2.y - point1.y) * (x - point1.x )) / (point2.x - point1.x)) + point1.y;
			my_mlx_pixel_put(&(vars->data), x, y, 0x00FFFFFF);
			x++;
		}
	}
}


void	draw_lines(t_vars *vars, int i, int j)
{
	t_2d_point point1;
	t_2d_point point2;

	point1.x = vars->shape_2d[i][j].value[0][0];
	point1.y = vars->shape_2d[i][j].value[1][0];
	if (i + 1 < vars->height)
	{
		point2.x = vars->shape_2d[i + 1][j].value[0][0];
		point2.y = vars->shape_2d[i + 1][j].value[1][0];
		line_between_2points(vars, point1, point2);
	}
	if (j + 1 < vars->width)
	{
		point2.x = vars->shape_2d[i][j + 1].value[0][0];
		point2.y = vars->shape_2d[i][j + 1].value[1][0];
		line_between_2points(vars, point1, point2);
		draw_lines(vars, i, j + 1);
	}
}

void	draw_map(t_vars *vars)
{
	int	i;
	// int	j;
	// t_2d_point	point2d;

	shape_3d_to_2d(vars);//
	// i = 0;
	// while (i < vars->height)
	// {
	// 	j = 0;
	// 	while (j < vars->width)
	// 	{
	// 		point2d.x = vars->shape_2d[i][j].value[0][0];
	// 		point2d.y = vars->shape_2d[i][j].value[1][0];
	// 		draw_circle(&(vars->data), 2, point2d);
	// 		// my_mlx_pixel_put(&(vars->data), point2d.x, point2d.y, 0x00FFFFFF);

	// 		j++;
	// 	}
	// 	i++;
	// }

	i = 0;
	while (i < vars->height)
	{
		draw_lines(vars, i++, 0);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
}

t_vars	init_vars(t_matrix **shape_3d, int height, int width)
{
	t_img_data	data;
	t_vars vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH , WINDOW_HEIGHT, "fdf");
	data.img = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	vars.data = data;
	vars.shape_3d = shape_3d;//
	mlx_hook(vars.win, 2, 1L<<0, handle_keys, &vars);
	vars.width = width;
	vars.height = height;
	return (vars);
}

void	fdf(t_matrix **shape, int height, int width)
{
	// t_point point;
	t_vars vars;
 
	vars = init_vars(shape, height, width);

	draw_map(&vars);
	mlx_loop(vars.mlx);
}

char **map_file_to_chars(char *file)
{
	char **map;
	char *str;
	char *tmp;


	int fd = open(file, O_RDONLY);
	if (fd < 0)
		return 0;
	str = ft_strdup("");
	int readed;
	tmp = (char *)malloc(sizeof(char) * 1000001);
	readed = 1;


	while (readed > 0)
	{
		readed = read(fd, tmp , 1000000);
		tmp[readed] = '\0';
		str = ft_strjoin(str, tmp);
		// printf("readed = %d | tmp %s\n", readed, tmp);

	}
	free(tmp);
	map = ft_split(str, '\n');
	free(str);
	close(fd);
	return (map);
}

float	**new_value(int x, int y, int z, int dimension)
{
	float	**value;
	int		i;

	value = (float **)malloc(sizeof(float *) * (dimension));
	i = 0;
	while (i < dimension)
	{
		value[i] = (float *)malloc(sizeof(float));
		i++;
	}
	value[0][0] = (float)x;
	value[1][0] = (float)y;
	if (dimension == 3)
	{
		value[2][0] = (float)z;
	}
	return (value);
}

t_matrix **map_chars_to_matrices(char **chars_map, int *height, int *width)
{
	t_matrix	**shape_3d;
	int	i;
	int j;
	char **tmp_ptr;

	tmp_ptr = ft_split(chars_map[0], ' ');
	while(tmp_ptr[*width] != NULL)
		*width += 1;
	free_all(tmp_ptr, *width - 1);
	while (chars_map[*height] != NULL)
		*height += 1;
	shape_3d = (t_matrix **)malloc(sizeof(t_matrix *) * (*height));
	i = 0;
	while (i < *height)
	{
		shape_3d[i] = (t_matrix *)malloc(sizeof(t_matrix) * (*width));
		i++;
	}
	i = 0;
	while (i < *height)
	{
		tmp_ptr = ft_split(chars_map[i], ' ');
		j = 0;
		while (j < *width)
		{
			(shape_3d[i][j]).value = new_value(i, j, ft_atoi(tmp_ptr[j]), 3);
			j++;
		}
		free_all(tmp_ptr, *width);
		i++;
	}
	return (shape_3d);
}


int main(int ac, char **av)
{
	char	**chars_map;
	t_matrix		**shape_3d;
	int		height;
	int		width;

	height = 0;
	width = 0;
	if (ac != 2)
		return (1);
	chars_map = map_file_to_chars(av[1]);
	// exit(0);
	if (chars_map == 0)
		return (0);
	shape_3d = map_chars_to_matrices(chars_map, &height, &width);
	fdf(shape_3d, height, width);
	return 0;
}
