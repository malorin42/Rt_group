/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahus <jbahus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 12:42:18 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/09 12:53:33 by jbahus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void			color_standard(t_env *env, t_double3 color, int *xy, int index)
{
	t_color		rgb_color;

	rgb_color.b.a = 0x00;
	rgb_color.b.r = 255 * max_double(0, min_double(1, color.x));
	rgb_color.b.g = 255 * max_double(0, min_double(1, color.y));
	rgb_color.b.b = 255 * max_double(0, min_double(1, color.z));
	color_pixel_image(rgb_color, (WIDTH * xy[1] + xy[0]) * env->img[index]->opp,
		env->img[index]);
}
