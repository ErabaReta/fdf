/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 18:21:55 by eouhrich          #+#    #+#             */
/*   Updated: 2024/04/30 19:11:09 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "../fdf.h"
#include <stdio.h>
#include <time.h>
# ifndef CLOCK_MONOTONIC
# define CLOCK_MONOTONIC 1
#endif

# define ROTATION_ANGLE ((M_PI / 180.0) / 10)
# define TRANSLATION_DIST ((ft_min(get_vars()->width, get_vars()->height) / 200))
void	normalise_and_rerender(t_vars *vars);


#endif