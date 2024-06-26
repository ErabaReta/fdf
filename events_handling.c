/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:28:41 by eouhrich          #+#    #+#             */
/*   Updated: 2024/04/30 16:28:04 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_close(void)
{
	fdf_exiter(get_vars());
	return (0);
}

int	handle_keys(int keycode, t_vars *garbage)
{
	t_vars	*vars;

	(void)garbage;
	vars = get_vars();
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		fdf_exiter(vars);
	}
	return (0);
}
