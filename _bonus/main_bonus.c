/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:26:41 by eouhrich          #+#    #+#             */
/*   Updated: 2024/05/01 21:22:02 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	my_mlx_pixel_put(t_img_data *data, int x, int y, int color)
{
	char			*dst;
	int				offset;
	unsigned int	*ptr;

	if (y >= WIN_HEIGHT || x >= WIN_WIDTH || x < 0 || y < 0)
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

// void	*ft_memset(void *b, int c, size_t len)
// {
// 	size_t			i;
// 	unsigned char	*tmp_str;

// 	tmp_str = (unsigned char *)b;
// 	i = 0;
// 	while (i < len)
// 	{
// 		tmp_str[i] = (unsigned char)c;
// 		i++;
// 	}
// 	return (b);
// }

void	clear_image(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			my_mlx_pixel_put(&(vars->data), j, i, 0x00);
			j++;
		}
		i++;
	}
	// ft_memset(vars->data.addr, 0, (size_t )(WIN_HEIGHT * WIN_WIDTH) * (vars->data.bits_per_pixel / 8));
}

// void print_fps(void)
// {
// 	static struct timespec last_time ; 
//     struct timespec current_time;
//     static int frame_count = 0;
	
//     if (last_time.tv_sec == 0 && last_time.tv_nsec == 0)
// 		clock_gettime(CLOCK_MONOTONIC, &last_time);
//     frame_count++;
//     clock_gettime(CLOCK_MONOTONIC, &current_time);
//     double elapsed = (current_time.tv_sec - last_time.tv_sec) +
//                      (current_time.tv_nsec - last_time.tv_nsec) / 1000000000.0;
// 	if (elapsed >= 1.0)
// 	{
// 		fprintf(stderr, "FPS: %d\n", frame_count);
// 		frame_count = 0;
// 		last_time = current_time;
//     }
// }

void update_attributes(void)
{
	get_vars()->xangle += get_vars()->update_xangle * ROTATION_ANGLE;
	get_vars()->yangle += get_vars()->update_yangle * ROTATION_ANGLE;
	get_vars()->zangle += get_vars()->update_zangle * ROTATION_ANGLE;

	get_vars()->xtranslation += get_vars()->update_xtranslation * TRANSLATION_DIST;
	get_vars()->ytranslation += get_vars()->update_ytranslation * TRANSLATION_DIST;
	get_vars()->ztranslation += get_vars()->update_ztranslation * TRANSLATION_DIST;
}

int loop(void)
{
	update_attributes();
	normalise_and_rerender(get_vars());
	// print_fps();
    return 0;
}


void	fdf(t_3d_point **shape, int height, int width)
{
	t_vars	vars;

	vars = init_vars(shape, height, width);
	mlx_loop_hook(vars.mlx, loop, NULL);
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
	if (check_file_name(av[1], ac) == -1)
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
