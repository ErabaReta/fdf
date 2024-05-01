/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:55:52 by eouhrich          #+#    #+#             */
/*   Updated: 2024/05/01 19:21:19 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	init_shape(t_vars *vars)
{
	vars->projection = 'o';
	vars->coords_sestym = 'c';
	if (vars->orthognal_type == 'i')
	{
		vars->xangle = (90 - 35.264) * (M_PI / 180);
		vars->yangle = 0 * (M_PI / 180);
		vars->zangle = -45 * (M_PI / 180);
		vars->zoom = 500.0 / ft_max(ft_max(vars->width, vars->height),
				vars->top_z);
	}
	else
	{
		vars->xangle = 0;
		vars->yangle = 0;
		vars->zangle = 0;
		vars->zoom = 500.0 / ft_max(vars->width, vars->height);
	}
	vars->xtranslation = 0;
	vars->ytranslation = 0 ;
	vars->ztranslation = -8 * ((ft_max(vars->width, vars->height) / 13) + 1);
}

t_vars	init_vars(t_3d_point **shape_3d, int height, int width)
{
	t_vars		*vars;

	vars = get_vars();
	vars->mlx = mlx_init();
	if (vars->mlx != NULL)
	{
		vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "fdf");
		vars->data.img = mlx_new_image(vars->mlx, WIN_WIDTH, WIN_HEIGHT);
	}
	if (vars->mlx == NULL || vars->win == NULL || vars->data.img == NULL)
	{
		ft_putstr_fd("Error: mlx failed\n", 2);
		fdf_exiter(vars);
	}
	vars->data.addr = mlx_get_data_addr(vars->data.img,
			&(vars->data.bits_per_pixel), &(vars->data.line_length),
			&(vars->data.endian));
	vars->width = width;
	vars->height = height;
	vars->shape_3d = shape_3d;
	vars->orthognal_type = 'i';
	init_shape(vars);
	mlx_hook(vars->win, 2, 1L << 0, handle_keys, vars);
	mlx_hook(vars->win, 17, 1L << 0, ft_close, vars);
	return (*vars);
}
