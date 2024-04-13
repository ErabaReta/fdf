#include "fdf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
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
				my_mlx_pixel_put(img, j, i, 0x00FF0000);
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

int	handle_keys(int keycode, t_vars *vars)
{	
	static int x;
	static int y;

	if (keycode == 53) // ESC
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if ( keycode == 13) //w
	{
		y-=10;
	}
	if ( keycode == 1)// s
	{
		y+=10;
	}
	if ( keycode == 0) // a
	{
		x-=10;
	}
	if ( keycode == 2) // d
	{
		x+=10;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, (*vars).data.img, x, y);
	printf("%d\n", keycode);
	return (0);
}
// 13 == w
// 1 == s
// 0 == a

// 2 == d

// Define viewpoint
t_3d_point viewpoint = {0, 0, 0};


// Function to project a 3D point to a 2D point
t_2d_point projectPoint(t_3d_point point3d) {

// Define projection matrix (simple perspective projection)
float projection_matrix[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
};
    // Apply projection
    float x_proj = point3d.x * projection_matrix[0][0] + point3d.y * projection_matrix[1][0] + point3d.z * projection_matrix[2][0];
    float y_proj = point3d.x * projection_matrix[0][1] + point3d.y * projection_matrix[1][1] + point3d.z * projection_matrix[2][1];
    float z_proj = point3d.x * projection_matrix[0][2] + point3d.y * projection_matrix[1][2] + point3d.z * projection_matrix[2][2];

    // Normalize coordinates
    x_proj /= z_proj;
    y_proj /= z_proj;

    // Create 2D point
    t_2d_point point2d = {x_proj * 50 + 100, y_proj * 50 + 100};
    return point2d;
}

void	draw_map(t_vars *vars)
{
	t_2d_point	point2d;
	t_3d_point	point3d;
	int i;
	int	j;


	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			//The general equation of a sphere is: (x - a)² + (y - b)² + (z - c)² = r²
			//equation of plane is : a(x  - x0) + b(y - y0) + c(z - z0) = 0
			point3d.x = vars->shape[i][j].value[0][0] + 10;
			point3d.y = vars->shape[i][j].value[1][0] + 10;
			point3d.z = vars->shape[i][j].value[2][0] + 10;
			point2d = projectPoint(point3d);
			printf("the 3d point x = %f , y = %f ,  z = %f turn into 2d point x = %d ,  y = %d \n", point3d.x, point3d.y, point3d.z, point2d.x, point2d.y);
			draw_circle(&(vars->data), 1, point2d);
			j++;
		}
		i++;
	}
	// printf("width == %d | height == %d\n", width, height);
	// printf("window's width == %d | window's height == %d\n", width * 50, height * 50);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
}

t_vars	init_vars(t_matrix **shape, int height, int width)
{
	t_img_data	data;
	t_vars vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 500 , 500, "fdf");
	data.img = mlx_new_image(vars.mlx, 500, 500);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	vars.data = data;
	vars.shape = shape;//
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
	tmp = get_next_line(fd);
	str = ft_gnl_strdup("");
	if (str == NULL)
		return (0);
	while(tmp != NULL)
	{
		str = ft_gnl_strjoin(str, tmp);
		free(tmp);
		tmp = get_next_line(fd);
	}
	map = ft_split(str, '\n');
	close(fd);
	return (map);
}

float	**new_value(int	z, int x, int y)
{
	float	**value;
	int		i;

	value = (float **)malloc(sizeof(float *) * (3));
	i = 0;
	while (i < 3)
	{
		value[i] = (float *)malloc(sizeof(float));
		i++;
	}
	value[0][0] = (float)x;
	value[1][0] = (float)y;
	value[2][0] = (float)z;
	return (value);
}

t_matrix **map_chars_to_matrices(char **chars_map, int *height, int *width)
{
	t_matrix	**shape;
	int	i;
	int j;
	char **tmp_ptr;

	tmp_ptr = ft_split(chars_map[0], ' ');
	while(tmp_ptr[*width] != NULL)
		*width += 1;
	free_all(tmp_ptr, *width - 1);
	while (chars_map[*height] != NULL)
		*height += 1;
	shape = (t_matrix **)malloc(sizeof(t_matrix *) * (*height));
	i = 0;
	while (i < *height)
	{
		shape[i] = (t_matrix *)malloc(sizeof(t_matrix) * (*width));
		i++;
	}
	i = 0;
	while (i < *height)
	{
		tmp_ptr = ft_split(chars_map[i], ' ');
		j = 0;
		while (j < *width)
		{
			(shape[i][j]).value = new_value(ft_atoi(tmp_ptr[j]), i, j);
			j++;
		}
		free_all(tmp_ptr, *width);
		i++;
	}
	return (shape);
}


int main(int ac, char **av)
{
	char	**chars_map;
	t_matrix		**shape;
	int		height;
	int		width;

	height = 0;
	width = 0;
	if (ac != 2)
		return (1);
	chars_map = map_file_to_chars(av[1]);
	if (chars_map == 0)
		return (0);
	shape = map_chars_to_matrices(chars_map, &height, &width);
	fdf(shape, height, width);
	return 0;
}
