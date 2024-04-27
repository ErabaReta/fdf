#include "fdf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char	*dst;
	int offset;
	unsigned int *ptr;

	if (y >= WINDOW_HEIGHT || x >= WINDOW_WIDTH || x < 0 || y < 0)
		return ;
	offset = y * data->line_length + x * (data->bits_per_pixel / 8);
	dst = data->addr + offset;
	ptr = (unsigned int*)dst;
	*ptr = color;
}

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
	printf ("window closed\n");
	fdf_exiter(get_vars());
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
		fdf_exiter(vars);
	}
	else if ( keycode == Q)
		vars->xangle += ROTATION_ANGLE * (M_PI / 180);
	else if ( keycode == W)
		vars->xangle -= ROTATION_ANGLE * (M_PI / 180);
	else if ( keycode == A)
		vars->yangle += ROTATION_ANGLE * (M_PI / 180);
	else if ( keycode == S)
		vars->yangle -= ROTATION_ANGLE * (M_PI / 180);
	else if ( keycode == Z)
		vars->zangle += ROTATION_ANGLE * (M_PI / 180);
	else if ( keycode == X)
		vars->zangle -= ROTATION_ANGLE * (M_PI / 180);
	else if ( keycode == E)
		vars->xtranslation += TRANSLATION_DISTENCE;
	else if ( keycode == R)
		vars->xtranslation -= TRANSLATION_DISTENCE;
	else if ( keycode == D)
		vars->ytranslation += TRANSLATION_DISTENCE;
	else if ( keycode == F)
		vars->ytranslation -= TRANSLATION_DISTENCE;
		else if ( keycode == C)
		vars->ztranslation += TRANSLATION_DISTENCE;
	else if ( keycode == V)
		vars->ztranslation -= TRANSLATION_DISTENCE;
	else if (keycode == UP_ARROW)
		vars->zoom += 0.5;
	else if (keycode == DOWN_ARROW)
		vars->zoom -= 0.5;
	else if (keycode == SPACE)
	{
		if (vars->projection == 'o')
			vars->projection = 'p';
		else
			vars->projection = 'o';
	}
	else if (keycode == ENTER)
	{
		if (vars->coords_sestym == 'c')
			vars->coords_sestym = 's';
		else
			vars->coords_sestym = 'c';
		vars->zoom = 500.0 / ft_max(ft_max(vars->width ,vars->height), vars->top_z);
	}
	else if (keycode == DELETE)
	{
		if (vars->orthognal_type == 'i')
			vars->orthognal_type = 'p';
		else
			vars->orthognal_type = 'i';
		init_shape(vars);
	}
	else
	{
		return (0);
	}
	if (vars->zoom <= 0)
		vars->zoom = 0.5;
	if(vars->zoom > 1000.0)
		vars->zoom = 1000.0;
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
	return (0);
}

t_3d_point	turn_spheric(t_vars *vars, int i, int j)
{
		t_3d_point	point3d;
		float r;
		float alhpa;
		float beta;

		r = (vars->shape_3d[i][j].z + ft_max(ft_max(vars->width ,vars->height), vars->top_z)) * 0.75;
		alhpa = (((vars->shape_3d[i][j].x + (vars->height / 2)) * 360) / vars->width) * (M_PI / 180);
		beta  = (((vars->shape_3d[i][j].y + (vars->height / 2)) * 180) / vars->height)  * (M_PI / 180);
		point3d.x =   r * sin(-beta) * cos(-alhpa);
		point3d.y = r * sin(-beta) * sin(-alhpa);
		point3d.z =  r * cos(-beta);
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
	point3d = rotateZ_point(point3d, vars->zangle);
	point3d = rotateX_point(point3d, vars->xangle); 
	point3d = rotateY_point(point3d, vars->yangle);
	point3d.color = vars->shape_3d[i][j].color;
	point3d.x += vars->xtranslation;
	point3d.y += vars->ytranslation;
	point3d.z += vars->ztranslation;
	return (point3d);
}

t_2d_point perspective_projection(t_3d_point point3d, float fov)
{
	t_2d_point	point2d;
	float	x_proj;
	float	y_proj;

	if (point3d.z >= 0)
	{
		point2d.x = -1;
		point2d.y = -1;
		return point2d;
	}
    x_proj = (point3d.x * -10) / point3d.z;
    y_proj = (point3d.y * -10) / point3d.z;

    point2d.x = x_proj *  1 * fov + WINDOW_WIDTH / 2 ;
	point2d.y = y_proj * 1 * fov + WINDOW_HEIGHT / 2;

	point2d.color = point3d.color;//
    return point2d;
}

t_2d_point project_point(t_vars *vars, int i, int j)
{
	t_2d_point	point2d;
	t_3d_point	point3d;

	point3d = get_coords(vars, i, j);
	if (vars->projection == 'p')
	{
		return (perspective_projection(point3d, vars->zoom));
	}
    point2d.x = point3d.x * vars->zoom + WINDOW_WIDTH / 2;
    point2d.y = point3d.y * vars->zoom + WINDOW_HEIGHT / 2;
	point2d.color = point3d.color;
    return point2d;
}

float	ft_min(float nbr1, float nbr2)
{
	if (nbr1 >= nbr2)
		return (nbr2);
	return (nbr1);
}

float	ft_max(float nbr1, float nbr2)
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

void draw_scope(t_vars *vars)
{
	int i= 0;

	while (i < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(&(vars->data), WINDOW_HEIGHT /2 , i, 0xffffff);
		my_mlx_pixel_put(&(vars->data), i , WINDOW_HEIGHT /2, 0xffffff);
		i++;
	}
}

void	draw_map(t_vars *vars)
{
	int	i;
	int	j;
	int	end_i;
	int	end_j;

	if (get_coords(vars, 0, 0).z <= get_coords(vars, vars->height - 1, 0).z)
	{
		i = 0;
		end_i = vars->height - 1;
	}
	else
	{
		i = -(vars->height - 1);
		end_i = 0;
	}
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
		{
			draw_lines(vars, ft_abs(i), ft_abs(j));
			j++;
		}
		i++;
	}
	draw_scope(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
}

void	init_shape(t_vars *vars)
{
	vars->projection = 'o';
	vars->coords_sestym = 'c';
	if (vars->orthognal_type == 'i')
	{
		vars->xangle = (90 - 35.264) * (M_PI / 180);
		vars->yangle = 0 * (M_PI / 180);
		vars->zangle = -45 * (M_PI / 180);
		vars->zoom = 500.0 / ft_max(ft_max(vars->width ,vars->height), vars->top_z);
	}
	else
	{
		vars->xangle = 0;
		vars->yangle = 0;
		vars->zangle = 0;
		vars->zoom = 500.0 / ft_max(vars->width ,vars->height);
	}
	vars->xtranslation = -0 * TRANSLATION_DISTENCE;
	vars->ytranslation = 0 * TRANSLATION_DISTENCE;
	vars->ztranslation = -8 * TRANSLATION_DISTENCE;
}

t_vars	init_vars(t_3d_point **shape_3d, int height, int width)
{
	t_img_data	data;
	t_vars *vars;

	vars = get_vars();
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH , WINDOW_HEIGHT, "fdf");
	data.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	vars->data = data;
	vars->width = width;
	vars->height = height;
	vars->shape_3d = shape_3d;
	vars->orthognal_type = 'i';
	init_shape(vars);
	mlx_hook(vars->win, 2, 1L<<0, handle_keys, vars);
	mlx_hook(vars->win, 17, 1L<<0, ft_close, vars);
	return (*vars);
}

void	fdf(t_3d_point **shape, int height, int width)
{
	t_vars vars;
 
	vars = init_vars(shape, height, width);

	draw_map(&vars);
	mlx_loop(vars.mlx);
}

long	ft_atohex(char *str)
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
		if (z > 100)
			*color = WHITE;
		else if (z > 20)
			*color = BROWN;
		else if (z > 0 )
			*color = GREEN;
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
	tmp = ft_atohex(str + 3);
	if (tmp >= 2147483648)
		return (-1);
	*color = tmp;
	return (0);
}

int	new_value(int y, int x, char *str, t_3d_point *value)
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
	if (get_vars()->top_z < tmp_z)
		get_vars()->top_z = tmp_z;

	if (set_color(str, &(value->color), tmp_z) == -1)
	{
		ft_putstr_fd("Error: invalid color prototype 0xTTRRGGBB\n", 2);
		return (-1);
	}
	return (0);
}

t_3d_point **map_chars_to_coords(char **chars_map, int height, int width)
{
	t_3d_point	**shape_3d;
	int	i;
	int j;
	char **tmp_ptr;

	shape_3d = (t_3d_point **)malloc(sizeof(t_3d_point *) * (height));
	i = 0;
	while (i < height)
	{
		shape_3d[i] = (t_3d_point *)malloc(sizeof(t_3d_point) * (width));
		i++;
	}
	i = 0;
	while (i < height)
	{
		tmp_ptr = ft_split(chars_map[i], ' ');
		j = 0;
		while (j < width)
		{
			if (new_value(i  - (height / 2), j  - (width / 2), tmp_ptr[j], &(shape_3d[i][j])) == -1)
				return free_all(tmp_ptr, width);
			j++;
		}
		free_all(tmp_ptr, width);
		i++;
	}
	return (shape_3d);
}



int main(int ac, char **av)
{
	char	**chars_map;
	t_3d_point		**shape_3d;
	int		height;
	int		width;

	height = 0;
	width = 0;
	if (ac > 2 || check_file_name(av[1]) == -1)
		return (1);
	chars_map = map_file_to_chars(av[1]);
	if (chars_map == 0 || check_height_width(chars_map, &height, &width))
	{
		free_all(chars_map, height);
		return (1);
	}
	get_vars()->top_z = 0;
	shape_3d = map_chars_to_coords(chars_map, height, width);
	free_all(chars_map, height);//
	if (shape_3d == NULL)
		return (1);
	fdf(shape_3d, height, width);
	return (0);
}



