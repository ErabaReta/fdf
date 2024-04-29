/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:41 by eouhrich          #+#    #+#             */
/*   Updated: 2024/04/29 11:32:30 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char			*dst;
	int				offset;
	unsigned int	*ptr;

	if (y >= WINDOW_HEIGHT || x >= WINDOW_WIDTH || x < 0 || y < 0)
		return ;
	offset = y * data->line_length + x * (data->bits_per_pixel / 8);
	dst = data->addr + offset;
	ptr = (unsigned int *)dst;
	*ptr = color;
}

t_vars	*get_vars(void)
{
	static t_vars	vars;

	return (&vars);
}

void	clear_image(t_vars *vars)
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

void	fdf(t_3d_point **shape, int height, int width)
{
	t_vars	vars;

	vars = init_vars(shape, height, width);
	draw_map(&vars);
	mlx_loop(vars.mlx);
}

int	main(int ac, char **av)
{
	char		**chars_map;
	t_3d_point	**shape_3d;
	int			height;
	int			width;

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
	free_all(chars_map, height);
	if (shape_3d == NULL)
		return (1);
	fdf(shape_3d, height, width);
	return (0);
}
