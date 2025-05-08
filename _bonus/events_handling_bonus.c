/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_handling_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:28:41 by eouhrich          #+#    #+#             */
/*   Updated: 2024/04/30 16:50:00 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_close(void)
{
	fdf_exiter(get_vars());
	return (0);
}

void	handle_shape_events(int keycode, t_vars *vars)
{
	if (keycode == Q)
		vars->update_xangle = 1;
	else if (keycode == W)
		vars->update_xangle = -1;
	else if (keycode == A)
		vars->update_yangle = 1;
	else if (keycode == S)
		vars->update_yangle = -1;
	else if (keycode == Z)
		vars->update_zangle = 1;
	else if (keycode == X)
		vars->update_zangle = -1;
	else if (keycode == E)
		vars->update_xtranslation = 1;
	else if (keycode == R)
		vars->update_xtranslation = -1;
	else if (keycode == D)
		vars->update_ytranslation = 1;
	else if (keycode == F)
		vars->update_ytranslation = -1;
	else if (keycode == C)
		vars->update_ztranslation = 1;
	else if (keycode == V)
		vars->update_ztranslation = -1;
	// if (keycode == Q)
	// 	vars->xangle += ROTATION_ANGLE;
	// else if (keycode == W)
	// 	vars->xangle -= ROTATION_ANGLE;
	// else if (keycode == A)
	// 	vars->yangle += ROTATION_ANGLE;
	// else if (keycode == S)
	// 	vars->yangle -= ROTATION_ANGLE;
	// else if (keycode == Z)
	// 	vars->zangle += ROTATION_ANGLE;
	// else if (keycode == X)
	// 	vars->zangle -= ROTATION_ANGLE;
	// else if (keycode == E)
	// 	vars->xtranslation += TRANSLATION_DIST;
	// else if (keycode == R)
	// 	vars->xtranslation -= TRANSLATION_DIST;
	// else if (keycode == D)
	// 	vars->ytranslation += TRANSLATION_DIST;
	// else if (keycode == F)
	// 	vars->ytranslation -= TRANSLATION_DIST;
	// else if (keycode == C)
	// 	vars->ztranslation += TRANSLATION_DIST;
	// else if (keycode == V)
	// 	vars->ztranslation -= TRANSLATION_DIST;
}

void	handle_display_events(int keycode, t_vars *vars)
{
	if (keycode == SPACE)
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
		vars->zoom = 500.0 / ft_max(ft_max(vars->width, vars->height),
				vars->top_z);
	}
	else if (keycode == DELETE)
	{
		if (vars->orthognal_type == 'i')
			vars->orthognal_type = 'p';
		else
			vars->orthognal_type = 'i';
		init_shape(vars);
	}
}

void	normalise_and_rerender(t_vars *vars)
{
	if (vars->zoom <= 0)
		vars->zoom = 0.5;
	if (vars->zoom > 1000.0)
		vars->zoom = 1000.0;
	if (vars->xangle >= (2 * M_PI))
		vars->xangle -= (2 * M_PI);
	if (vars->yangle >= (2 * M_PI))
		vars->yangle -= (2 * M_PI);
	if (vars->zangle >= (2 * M_PI))
		vars->zangle -= (2 * M_PI);
	if (vars->xangle <= -(2 * M_PI))
		vars->xangle += (2 * M_PI);
	if (vars->yangle <= -(2 * M_PI))
		vars->yangle += (2 * M_PI);
	if (vars->zangle <= -(2 * M_PI))
		vars->zangle += (2 * M_PI);
	clear_image(vars);
	draw_map(vars);
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
	else if (keycode == Q || keycode == W || keycode == A || keycode == S
		|| keycode == Z || keycode == X || keycode == E || keycode == R
		|| keycode == D || keycode == F || keycode == C || keycode == V)
		handle_shape_events(keycode, vars);
	else if (keycode == UP_ARROW)
		vars->zoom += 0.5;
	else if (keycode == DOWN_ARROW)
		vars->zoom -= 0.5;
	else if (keycode == SPACE || keycode == ENTER || keycode == DELETE)
		handle_display_events(keycode, vars);
	// else
	return (0);
	// normalise_and_rerender(vars);
	// return (0);
}


int key_release(int keycode, void *garbage)
{
	(void)garbage;
	if (keycode == Q)
		get_vars()->update_xangle = 0;
	else if (keycode == W)
		get_vars()->update_xangle = 0;
	else if (keycode == A)
		get_vars()->update_yangle = 0;
	else if (keycode == S)
		get_vars()->update_yangle = 0;
	else if (keycode == Z)
		get_vars()->update_zangle = 0;
	else if (keycode == X)
		get_vars()->update_zangle = 0;
	else if (keycode == E)
		get_vars()->update_xtranslation = 0;
	else if (keycode == R)
		get_vars()->update_xtranslation = 0;
	else if (keycode == D)
		get_vars()->update_ytranslation = 0;
	else if (keycode == F)
		get_vars()->update_ytranslation = 0;
	else if (keycode == C)
		get_vars()->update_ztranslation = 0;
	else if (keycode == V)
		get_vars()->update_ztranslation = 0;
	return (0);
}