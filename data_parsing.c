/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:31:53 by eouhrich          #+#    #+#             */
/*   Updated: 2024/04/28 11:31:54 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		if (str[i] >= '0' && str[i] <= '9')
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

int	color_decider(int *color, int z)
{
	if (z > 100)
		*color = WHITE;
	else if (z > 20)
		*color = BROWN;
	else if (z > 0)
		*color = GREEN;
	else
		*color = BLUE;
	return (0);
}

int	set_color(char *str, int *color, int z)
{
	int		i;
	long	tmp;

	while (*str != ',' && *str != '\0')
		str++;
	if (*str == '\0')
		return (color_decider(color, z));
	if (ft_strncmp(str, ",0x", 3) != 0)
		return (-1);
	ft_str_tolower(str);
	i = 3;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 'a' && str[i] <= 'f')
			&& !(str[i] >= '0' && str[i] <= '9'))
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

	tmp_z = ft_atoi(str);
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

t_3d_point	**map_chars_to_coords(char **chars_map, int height, int width)
{
	t_3d_point	**shape_3d;
	int			i;
	int			j;
	char		**tmp_ptr;

	shape_3d = (t_3d_point **)malloc(sizeof(t_3d_point *) * (height));
	i = 0;
	while (i < height)
		shape_3d[i++] = (t_3d_point *)malloc(sizeof(t_3d_point) * (width));
	i = 0;
	while (i < height)
	{
		tmp_ptr = ft_split(chars_map[i], ' ');
		j = 0;
		while (j < width)
		{
			if (new_value(i  - (height / 2), j  - (width / 2),
				tmp_ptr[j], &(shape_3d[i][j])) == -1)
				return free_all(tmp_ptr, width);
			j++;
		}
		free_all(tmp_ptr, width);
		i++;
	}
	return (shape_3d);
}
