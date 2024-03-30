#include "fdf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_mostatil(t_data *img, int l3ard, int tol, t_point point)
{
	int i = 0;
	int j = 0;

	while (i < l3ard)
	{
		j = 0;
		while (j < tol)
		{
			printf("writed a pixel to x == %d   y == %d\n", point.x + j, point.y + i );
			my_mlx_pixel_put(img, point.x + j, point.y + i, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void	draw_mo3ayan(t_data *img, int l3ard, int tol, t_point point)
{
	int i =0;
	int j =0;

	(void)tol;
	while (i < l3ard)
	{
		j = 0;
		while (j < i)
		{
			my_mlx_pixel_put(img, point.x + j, point.y + i, 0x00FF0000);
			j++;
		}
		j = 0;
		while (j < i)
		{
			my_mlx_pixel_put(img, point.x - j, point.y + i, 0x00FF0000);
			j++;
		}
		i++;
	}
	int k = 0;
	while (i < 2 * l3ard)
	{
		j = l3ard - k;
		while (j >= 0)
		{
			my_mlx_pixel_put(img, point.x + j, point.y + i, 0x00FF0000);
			j--;
		}
		j = l3ard - k;
		while (j >= 0)
		{
			my_mlx_pixel_put(img, point.x - j, point.y + i, 0x00FF0000);
			j--;
		}
		k++;
		i++;
	}


}

int	ft_power(int nbr, int power)
{
	int i = 0;
	int r = 1;
	while (i < power)
	{
		r *= nbr;
		i++;
	}
	return (r);
}

int ft_abs(int nbr)
{
	return (((nbr >= 0) - (nbr < 0 )) * nbr);
}



int calc_dist(int x, int y, t_point point)
{
	int r;

	r = sqrt(ft_power(ft_abs(x - point.x), 2) + ft_power(ft_abs(y - point.y), 2));
	return (r);
}

void	draw_circle(t_data *img, int cho3a3, t_point point)
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
				printf("pixeled the point x ==%d  | y == %d | with dist == %d\n", j, i, calc_dist(j, i, point));
				my_mlx_pixel_put(img, j, i, 0x00FF0000);
			}
			j++;
		}
		i++;
	}

}

int	draw(int button, int x, int y, void *ptr)
{
	t_point point;

	point.x = x;
	point.y = y;

	(void)button;
	t_vars *vars = (t_vars *)ptr;
	draw_circle((vars->data), 10, point);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
	return (0);
}

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
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, x, y);
	printf("%d\n", keycode);
	return (0);
}
// 13 == w
// 1 == s
// 0 == a

// 2 == d

void	draw_map(t_vars *vars,int **map, int height, int width)
{
	t_point	position;
	int i;
	int	j;
	
	(void)map;

	i = 10;
	while (i < height + 10)
	{
		j = 10;
		position.y = i * 20;
		while (j < width + 10)
		{
			position.x = j * 20;
			draw_circle(vars->data, 1, position);
			printf("write pixel to x==%d | y==%d\n", position.x, position.y);
			j++;
		}
		i++;
	}
	printf("width == %d | height == %d\n", width, height);
	printf("window's width == %d | window's height == %d\n", width * 50, height * 50);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data->img, 0, 0);
}

void	fdf(int **map, int height, int width)
{
	t_data	data;
	// t_point point;
	t_vars vars;
 
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, width * 50 , height * 50, "fdf");
	data.img = mlx_new_image(vars.mlx, width * 50, height * 50);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	vars.data = &data;
// 	mlx_hook(vars.win, 4, 1L<<0, draw, &vars);
	mlx_hook(vars.win, 2, 1L<<0, handle_keys, &vars);

	draw_map(&vars,map, height, width);
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

int **map_chars_to_ints(char **chars_map, int *height, int *width)
{
	int	**ints_map;
	int	i;
	int j;
	char **tmp_ptr;

	tmp_ptr = ft_split(chars_map[0], ' ');
	while(tmp_ptr[*width] != NULL)
		*width += 1;
	free_all(tmp_ptr, *width - 1);
	while (chars_map[*height] != NULL)
		*height += 1;
	ints_map = (int **)malloc(sizeof(int *) * (*height));
	i = 0;
	while (i < *height)
	{
		ints_map[i] = (int *)malloc(sizeof(int) * (*width));
		i++;
	}
	i = 0;
	while (i < *height)
	{
		tmp_ptr = ft_split(chars_map[i], ' ');
		j = 0;
		while (j < *width)
		{
			ints_map[i][j] = ft_atoi(tmp_ptr[j]);
			j++;
		}
		free_all(tmp_ptr, *width);
		i++;
	}
	return (ints_map);
}


int main(int ac, char **av)
{
	char	**chars_map;
	int		**ints_map;
	int		height;
	int		width;

	height = 0;
	width = 0;
	if (ac != 2)
		return (1);
	chars_map = map_file_to_chars(av[1]);
	if (chars_map == 0)
		return (0);
	ints_map = map_chars_to_ints(chars_map, &height, &width);
	fdf(ints_map, height, width);
	return 0;
}
