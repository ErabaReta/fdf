/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:30:08 by eouhrich          #+#    #+#             */
/*   Updated: 2024/04/28 18:52:03 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_height_width(char **chars_map, int *height, int *width)
{
	int	tmp;

	*width = count_words(chars_map[0], ' ');
	while (chars_map[*height] != NULL)
	{
		tmp = count_words(chars_map[*height], ' ');
		if (tmp < *width)
		{
			ft_putstr_fd("Error: wrong line lenght\n", 2);
			return (-1);
		}
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

char	**reader(int fd, char *str, char *tmp)
{
	int		readed;
	char	**map;

	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, tmp, 1000000);
		tmp[readed] = '\0';
		str = ft_strjoin(str, tmp);
		if (str == NULL)
		{
			ft_putstr_fd("Error: malloc failed to allocate\n", 2);
			return (0);
		}
	}
	map = ft_split(str, '\n');
	free(tmp);
	free(str);
	close(fd);
	return (map);
}

char	**map_file_to_chars(char *file)
{
	char	*tmp;
	char	*str;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: invalid file or permession\n", 2);
		return (0);
	}
	str = ft_strdup("");
	tmp = (char *)malloc(sizeof(char) * 1000001);
	if (file == NULL || tmp == NULL)
	{
		ft_putstr_fd("Error: malloc failed to allocate\n", 2);
		return (0);
	}
	return (reader(fd, str, tmp));
}
