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


void	fdf(t_3d_point **shape, int height, int width)
{
	t_vars vars;
 
	vars = init_vars(shape, height, width);
	draw_map(&vars);
	mlx_loop(vars.mlx);
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



