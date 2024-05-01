/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:21:15 by eouhrich          #+#    #+#             */
/*   Updated: 2024/05/01 21:22:53 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_exiter(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->height)
	{
		free(vars->shape_3d[i]);
		i++;
	}
	free(vars->shape_3d);
	exit(0);
}
