/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:01:08 by eouhrich          #+#    #+#             */
/*   Updated: 2024/03/08 17:57:13 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*deviser(char **big_string)
{
	int		newl_i;
	char	*rest;
	char	*tmp;

	newl_i = ft_gnl_strlen(*big_string, 1);
	if (newl_i == -1)
		rest = ft_gnl_strdup("");
	else
	{
		rest = ft_gnl_substr(*big_string, newl_i + 1,
				ft_gnl_strlen(*big_string, 2));
		tmp = *big_string;
		*big_string = ft_gnl_substr(*big_string, 0, newl_i + 1);
		free(tmp);
	}
	return (rest);
}

int	reader(char **buffer, ssize_t *readed, char **big_string, int fd)
{
	*buffer = (char *)malloc(sizeof(char) * (2));
	if (*buffer == NULL)
	{
		if (*big_string != NULL)
			free(*big_string);
		return (0);
	}
	*readed = read(fd, *buffer, 1);
	if (*buffer == NULL || *readed <= 0)
	{
		free(*buffer);
		if (*readed == 0 && *big_string != NULL)
			return (1);
		free(*big_string);
		return (0);
	}
	buffer[0][*readed] = '\0';
	*big_string = ft_gnl_strjoin(*big_string, *buffer);
	if (ft_gnl_strlen(*buffer, 1) != -1 || *readed != 1)
	{
		free(*buffer);
		return (1);
	}
	free(*buffer);
	return (2);
}

int	rester(char **big_string, char **rest)
{
	*big_string = ft_gnl_strjoin(*big_string, *rest);
	free(*rest);
	if (*big_string == NULL)
		return (0);
	*rest = NULL;
	if (ft_gnl_strlen(*big_string, 1) != -1)
	{
		*rest = deviser(big_string);
		if (*rest == NULL || *big_string == NULL)
			return (0);
		if (ft_gnl_strlen(*rest, 2) == 0)
		{
			free(*rest);
			*rest = NULL;
		}
		big_string[0][ft_gnl_strlen(*big_string, 2)] = '\0';
		return (1);
	}
	return (2);
}

int	return_handler(char **big_string, char **rest, char **buffer, int fd)
{
	ssize_t		readed;
	int			returned;

	*big_string = NULL;
	if (*rest != NULL)
	{
		returned = rester(big_string, rest);
		if (returned == 0)
			return (0);
		if (returned == 1)
			return (1);
	}
	readed = 1;
	while (readed > 0)
	{
		returned = reader(buffer, &readed, big_string, fd);
		if (returned == 1)
			break ;
		if (returned == 0)
			return (0);
	}
	*rest = deviser(big_string);
	if (*rest == NULL)
		return (0);
	return (2);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*big_string;
	int			returned;
	static char	*rest;

	if (fd < 0)
		return (NULL);
	returned = return_handler(&big_string, &rest, &buffer, fd);
	if (returned == 0)
		return (NULL);
	if (returned == 1)
		return (big_string);
	if (ft_gnl_strlen(rest, 2) == 0)
	{
		free(rest);
		rest = NULL;
	}
	big_string[ft_gnl_strlen(big_string, 2)] = '\0';
	return (big_string);
}
