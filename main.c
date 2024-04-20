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

// void	draw_circle(t_img_data *img, int cho3a3, t_2d_point point)
// {
// 	int i = point.y - cho3a3;
// 	int j;

// 	// while (i < 299)
// 	// {
// 	// 	j = 0;
// 	// 	while (j < 299)
// 	// 	{
// 	// 		if (  (ft_power(ft_abs(j - point.x), 2) + ft_power(ft_abs(i - point.y), 2))       == ft_power(cho3a3, 2))
// 	// 		my_mlx_pixel_put(img, j, i, 0x00FF0000);
// 	// 		j++;
// 	// 	}
// 	// 	i++;
// 	// }
// 	while (i < point.y + cho3a3)
// 	{
// 		j = point.x - cho3a3;
// 		while (j < point.x + cho3a3)
// 		{
// 			if (calc_dist(j, i, point) <= cho3a3)
// 			{
// 				// printf("pixeled the point x ==%d  | y == %d | with dist == %d\n", j, i, calc_dist(j, i, point));
// 				my_mlx_pixel_put(img, j, i, 0x00FFFFFF);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

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

t_vars	*get_vars(void)
{
	static t_vars	vars;

	return (&vars);
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
				vars->shape_3d[i][j].x += distence;
			else if (axis == 'y')
				vars->shape_3d[i][j].y += distence;
			else if (axis == 'z')
				vars->shape_3d[i][j].z += distence;
			j++;
		}
		i++;
	}
}

int	ft_close(void)
{
	t_vars *vars;

	vars = get_vars();
	// mlx_destroy_window(vars->mlx, vars->win);
	// system("leaks fdf");
	printf ("window closed\n");
	exit(0);
	return (0);
}

int	handle_keys(int keycode, t_vars *garbage)
{
	t_vars *vars;

	(void)garbage;
	vars = get_vars();
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		// system("leaks fdf");
		exit(0);
	}
	else if ( keycode == Q)
	{
		// rotate_shape(vars, ROTATION_ANGLE * (M_PI / 180), 'x');
		vars->xangle += ROTATION_ANGLE * (M_PI / 180) ;
	}
	else if ( keycode == W)
	{
		// rotate_shape(vars, -ROTATION_ANGLE * (M_PI / 180), 'x');
		vars->xangle -= ROTATION_ANGLE * (M_PI / 180);
	}
	else if ( keycode == A)
	{
		// rotate_shape(vars, 2 * (M_PI / 180), 'y');
		vars->yangle += ROTATION_ANGLE * (M_PI / 180);
	}
	else if ( keycode == S)
	{
		// rotate_shape(vars, -ROTATION_ANGLE * (M_PI / 180), 'y');
		vars->yangle -= ROTATION_ANGLE * (M_PI / 180);
	}
		else if ( keycode == Z)
	{
		// rotate_shape(vars, ROTATION_ANGLE * (M_PI / 180), 'z');
		vars->zangle += ROTATION_ANGLE * (M_PI / 180);
	}
		else if ( keycode == X)
	{
		// rotate_shape(vars, -ROTATION_ANGLE * (M_PI / 180), 'z');
		vars->zangle -= ROTATION_ANGLE * (M_PI / 180);
	}
		else if ( keycode == E)
	{
		// translate_shape(vars, TRANSLATION_DISTENCE, 'x');
		vars->xtranslation += TRANSLATION_DISTENCE;
	}
		else if ( keycode == R)
	{
		// translate_shape(vars, -TRANSLATION_DISTENCE, 'x');
		vars->xtranslation -= TRANSLATION_DISTENCE;
	}
		else if ( keycode == D)
	{
		// translate_shape(vars, TRANSLATION_DISTENCE, 'y');
		vars->ytranslation += TRANSLATION_DISTENCE;
	}
		else if ( keycode == F)
	{
		// translate_shape(vars, -TRANSLATION_DISTENCE, 'y');
		vars->ytranslation -= TRANSLATION_DISTENCE;
	}
		else if ( keycode == C)
	{
		// translate_shape(vars, TRANSLATION_DISTENCE, 'z');
		vars->ztranslation += TRANSLATION_DISTENCE;
	}
		else if ( keycode == V)
	{
		// translate_shape(vars, -TRANSLATION_DISTENCE, 'z');
		vars->ztranslation -= TRANSLATION_DISTENCE;
	}
		else if (keycode == UP_ARROW)
	{
		vars->zoom += 0.5;
	}
		else if (keycode == DOWN_ARROW)
	{
		vars->zoom -= 0.5;
	}
	else
	{
		return (0);
	}
	if (vars->zoom <= 0)
		vars->zoom = 0.5;
	if (vars->xangle >= (2 * M_PI))
		vars->xangle -= (2 * M_PI);
	if (vars->yangle >= (2 * M_PI))
		vars->yangle -=  (2 * M_PI);
	if (vars->zangle >= (2 * M_PI))
		vars->zangle -= (2 * M_PI);

	if (vars->xangle <= -(2 * M_PI))
		vars->xangle += (2 * M_PI);
	if (vars->yangle <= -(2 * M_PI))
		vars->yangle +=  (2 * M_PI);
	if (vars->zangle <= -(2 * M_PI))
		vars->zangle += (2 * M_PI);
	clear_image(vars);
	draw_map(vars);
	// printf("xangle = %d | yangle = %d | zangle = %d \n");
	return (0);
}

t_3d_point	get_coords(t_vars *vars, int i, int j)
{
	t_3d_point	point3d;

	 point3d = vars->shape_3d[i][j];

	point3d = rotateZ_point(point3d, vars->zangle);
	point3d = rotateX_point(point3d, vars->xangle);
	point3d = rotateY_point(point3d, vars->yangle);



	point3d.color = vars->shape_3d[i][j].color;
	point3d.x += vars->xtranslation;
	point3d.y += vars->ytranslation;
	point3d.z += vars->ztranslation;
	return (point3d);
}

t_3d_point	apply_isometric(t_3d_point	point)
{
	t_3d_point new_point;

	new_point.x = sqrt(0.5) * point.x + -sqrt(0.5) * point.z;
	new_point.y = sqrt(0.1666666667) * point.x + sqrt(0.3333333333) * point.y + sqrt(0.1666666667) * point.z;
	new_point.z = sqrt(0.3333333333) * point.x + -sqrt(0.3333333333) * point.y + sqrt(0.3333333333) * point.z;
	new_point.color = point.color;
	return (new_point);
}

t_2d_point project_point(t_vars *vars, int i, int j)
{
	t_2d_point	point2d;
	t_3d_point	point3d;
	// float x_proj;
	// float y_proj;

	point3d = get_coords(vars, i, j);
	// printf("point 3d x = %f |||==>sqrt(3 / 6) = %d || -sqrt(3  / 6) => %f\n", point3d.x, sqrt(3 / 6) , -sqrt(3 / 6));
	// point3d = apply_isometric(point3d);
	// if (vars->proj)
	// if (point3d.z >= 0)
	// {
	// 	point2d.x = -1;
	// 	point2d.y = -1;
	// 	return point2d;
	// }
    // x_proj = (point3d.x * vars->zoom) / point3d.z;
    // y_proj = (point3d.y * (-vars->zoom)) / point3d.z;

    // point2d.x = x_proj * 100 + WINDOW_WIDTH / 2 ;
	// point2d.y = y_proj * 100 + WINDOW_HEIGHT / 2;

	// point2d.color = point3d.color;//
    // return point2d;


	//====================

    point2d.x = point3d.x * -vars->zoom + WINDOW_WIDTH / 2;
    point2d.y = point3d.y * vars->zoom + WINDOW_HEIGHT / 2;
	point2d.color = point3d.color;

	// printf("point 3d x = %f | y = %f | z = %f  turn into 2d point x = %d | y = %d\n", point3d.x, point3d.y, point3d.z, point2d.x, point2d.y);

    return point2d;
}

// void	shape_3d_to_2d(t_vars	*vars)
// {
// 	int 		i;
// 	int			j;

// 	i = 0;
// 	while (i < vars->height)
// 	{
// 		j = 0;
// 		while (j < vars->width)
// 		{
// 			//The general equation of a sphere is: (x - a)² + (y - b)² + (z - c)² = r²
// 			//equation of plane is : a(x  - x0) + b(y - y0) + c(z - z0) = 0
// 			// point3d.x = vars->shape_3d[i][j].x - 20;
// 			// point3d.y = vars->shape_3d.y  - 20;
// 			// point3d.z = (vars->shape_3d[i][j].value[2][0]) - 20;
// 			vars->shape_2d[i][j] = project_point(vars->shape_3d[i][j]);
// 			printf("the 3d point x = %f , y = %f ,  z = %f turn into 2d point x = %d ,  y = %d \n", vars->shape_3d[i][j].x, vars->shape_3d[i][j].y, vars->shape_3d[i][j].z, vars->shape_2d[i][j].x, vars->shape_2d[i][j].y);
// 			j++;
// 		}
// 		i++;
// 	}
// }

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



void	line_between_2points(t_vars	*vars, t_2d_point point1, t_2d_point point2, int color)
{
	int	x;
	int	y;

	if ((point1.x == -1 && point1.y == -1) || (point2.x == -1 && point2.y == -1))
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
			my_mlx_pixel_put(&(vars->data), x, y, color);
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
	t_2d_point point1;
	t_2d_point point2;
	int	color;

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
}

void	draw_map(t_vars *vars)
{
	int	i;
	int	j;
	// t_2d_point point2d;

	// i = 0;
	// while (i < vars->height)
	// {
	// 	j = 0;
	// 	while (j < vars->width)
	// 	{
	// // 		// draw_circle(&(vars->data), 2, point2d);
	// // 		point2d = project_point(vars, i, j);
	// // 		my_mlx_pixel_put(&(vars->data), point2d.x, point2d.y, 0x00FFFFFF);
	// 		j++;
	// 	}
	// 	i++;
	// }
	printf("xangle => %f || yangle => %f || zangle => %f\n", vars->xangle * (180 / M_PI), vars->yangle * (180 / M_PI), vars->zangle * (180 / M_PI));///
	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			draw_lines(vars, i, j);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
}

t_vars	init_vars(t_3d_point **shape_3d, int height, int width)
{
	t_img_data	data;
	t_vars *vars;
	// int	i;

	vars = get_vars();
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH , WINDOW_HEIGHT, "fdf");
	data.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	vars->data = data;
	vars->width = width;
	vars->height = height;
	vars->shape_3d = shape_3d;//
	vars->xangle = 60 * (M_PI / 180);//60 * (M_PI / 180);
	vars->yangle = 0 * (M_PI / 180);//0;
	vars->zangle = 135.264 * (M_PI / 180);//M_PI_2 ;
	vars->xtranslation = 0;
	vars->ytranslation = 4 * TRANSLATION_DISTENCE;
	vars->ztranslation = 0;
	vars->zoom = 600.0 / ft_max(width ,height );//4.5;
	mlx_hook(vars->win, 2, 1L<<0, handle_keys, vars);
	mlx_hook(vars->win, 17, 1L<<0, ft_close, vars);
	// mlx_key_hook(vars->win, handle_keys, vars);
	return (*vars);
}

void	fdf(t_3d_point **shape, int height, int width)
{
	// t_point point;
	t_vars vars;
 
	vars = init_vars(shape, height, width);

	draw_map(&vars);
	mlx_loop(vars.mlx);
}

char **map_file_to_chars(char *file)
{
	char	**map;
	char	*str;
	char	*tmp;
	int		readed;


	int fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: invalid file or permession\n", 2);
		return 0;
	}
	str = ft_strdup("");
	tmp = (char *)malloc(sizeof(char) * 1000001);
	if (str == NULL || tmp == NULL)
	{
		ft_putstr_fd("Error: malloc failed to allocate\n", 2);
		return 0;
	}
	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, tmp , 1000000);
		tmp[readed] = '\0';
		str = ft_strjoin(str, tmp);
		// printf("readed = %d | tmp %s\n", readed, tmp);
	}
	map = ft_split(str, '\n');
	close(fd);
	return (free(tmp), free(str), map);
}

long	ft_atoi_hex(char *str)
{
	size_t			i;
	size_t			nbr;
	int				counter;
	int				tmp;
	
	i = 0;
	counter = 0;
	nbr = 0;
	while (str[i] != '\0')
	{
		if(str[i] >= '0' && str[i] <= '9')
			tmp = str[i] - 48;
		else
			tmp = str[i] - 87;
		nbr = nbr * 16 + tmp;
		if (nbr >= 2147483648)
			return (2147483648);
		counter++;
		i++;
	}
	if (counter < 1)
		return (2147483648);
	return (nbr);
}

int	set_color(char *str, int *color, int z)
{
	int	i;
	long	tmp;
	(void)str;

	while (*str != ',' && *str != '\0')
		str++;
	if (*str == '\0')
	{
		// (void)z;
		if (z > 75)
			*color = WHITE;
		else if (z > 5)
			*color = BROWN;
		else if (z > -2)
			*color = GREEN;
		else if (z > -20)
			*color = CYAN;
		else
			*color = BLUE;
		return (0);
	}
	if (ft_strncmp(str, ",0x", 3) != 0)
		return (-1);
	ft_str_tolower(str);
	i = 3;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 'a' && str[i] <= 'f') && !(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	tmp = ft_atoi_hex(str + 3);
	if (tmp >= 2147483648)
		return (-1);
	*color = tmp;
	return (0);
}

int	new_value(int x, int y, char *str, t_3d_point *value)
{
	long		tmp_z;

	tmp_z  = ft_atoi(str);
	if (tmp_z > INT_MAX)
	{
		ft_putstr_fd("Error: invalide value in the map or may overflow\n", 2);
		return (-1);
	}
	value->x = (float)x;
	value->y = (float)y;
	value->z = (float)tmp_z;

	if (set_color(str, &(value->color), tmp_z) == -1)
	{
		ft_putstr_fd("Error: invalid color prototype 0xTTRRGGBB\n", 2);
		return (-1);
	}
	return (0);
}

t_3d_point **map_chars_to_coords(char **chars_map, int *height, int *width)
{
	t_3d_point	**shape_3d;
	int	i;
	int j;
	char **tmp_ptr;

	tmp_ptr = ft_split(chars_map[0], ' ');
	while(tmp_ptr[*width] != NULL)
		*width += 1;
	free_all(tmp_ptr, *width - 1);
	while (chars_map[*height] != NULL)
		*height += 1;
	shape_3d = (t_3d_point **)malloc(sizeof(t_3d_point *) * (*height));
	i = 0;
	while (i < *height)
	{
		shape_3d[i] = (t_3d_point *)malloc(sizeof(t_3d_point) * (*width));
		i++;
	}
	i = 0;
	while (i < *height)
	{
		tmp_ptr = ft_split(chars_map[i], ' ');
		j = 0;
		while (j < *width)
		{
			if (new_value(i - (*height / 2), j - (*width / 2), tmp_ptr[j], &(shape_3d[i][j])) == -1)
			{
				return free_all(tmp_ptr, *width);
			}
			j++;
		}
		free_all(tmp_ptr, *width);
		i++;
	}
	return (shape_3d);
}

int	check_height_width(char **chars_map, int *height, int *width)
{
	int	tmp;

	*width = count_words(chars_map[0], ' ');
	while (chars_map[*height] != NULL)
	{
		tmp = count_words(chars_map[*height], ' ');
		if (tmp != *width)
		{
			ft_putstr_fd("Error: wrong line lenght\n", 2);
			return (-1);
		}
		*width = tmp;
		*height += 1;
	}
	if (*width <= 0 || *height <= 0)
	{
		ft_putstr_fd("Error: no data found\n", 2);
		return (-1);
	}
	return (0);
}

int	check_file_name(char *file)
{
	if (ft_strlen(file) <= 4
		|| ft_strncmp(&file[ft_strlen(file) - 4], ".fdf", 4) != 0)
	{
		ft_putstr_fd("Error: file name should end with .fdf\n", 2);
		return (-1);
	}
	return (0);
}

int main(int ac, char **av)
{
	char	**chars_map;
	t_3d_point		**shape_3d;
	int		height;
	int		width;

	height = 0;
	width = 0;
	if (ac != 2 || check_file_name(av[1]) == -1)
		return (1);
	chars_map = map_file_to_chars(av[1]);
	if (chars_map == 0 || check_height_width(chars_map, &height, &width))
	{
		free_all(chars_map, height);
		return (1);
	}
	shape_3d = map_chars_to_coords(chars_map, &height, &width);
	// printf("height = > %d || width => %d\n", height, width);//

	// for (int i = 0; i < height; i++)
	// {
	// 	for (int j = 0; j < width ; j++)
	// 	{
	// 		printf("point[%d][%d]  x => %f | y => %f | z => %f\n", i, j, shape_3d[i][j].x, shape_3d[i][j].y, shape_3d[i][j].z);//
	// 	}
	// }
	//====================================
	// shape_3d[0][1].x = 0;
	// shape_3d[0][1].y = 0;
	// //=
	// shape_3d[0][2].x = 1;
	// shape_3d[0][2].y = 0;
	// //=
	// shape_3d[1][0].x = 0;
	// shape_3d[1][0].y = 0;
	// //=
	// shape_3d[1][1].x = 0;
	// shape_3d[1][1].y = 0;
	// //=
	// shape_3d[1][2].x = 1;
	// shape_3d[1][2].y = 0;
	// //=
	// shape_3d[1][3].x = 1;
	// shape_3d[1][3].y = 0;
	// //=
	// shape_3d[2][0].x = 0;
	// shape_3d[2][0].y = 1;
	// //=
	// shape_3d[2][1].x = 0;
	// shape_3d[2][1].y = 1;
	// //=
	// shape_3d[2][2].x = 1;
	// shape_3d[2][2].y = 1;
	// //=
	// shape_3d[2][3].x = 1;
	// shape_3d[2][3].y = 1;
	// //=
	// shape_3d[3][1].x = 0;
	// shape_3d[3][1].y = 1;
	// //=
	// shape_3d[3][2].x = 1;
	// shape_3d[3][2].y = 1;
	// //=

	//====================================
	if (shape_3d == NULL)
		return (1);
	fdf(shape_3d, height, width);
	return (0);
}



