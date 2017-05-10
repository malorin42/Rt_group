/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahus <jbahus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 12:42:18 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/09 16:37:49 by jbahus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static t_color		sepia(t_color rgb_color)
{
	t_color		sepia;

	sepia.b.a = 0x00;
	sepia.b.r = (unsigned char)((rgb_color.b.r * 0.393) + (rgb_color.b.g * 0.769) +
		(rgb_color.b.b * 0.189));
	sepia.b.g = (unsigned char)((rgb_color.b.r * 0.349) + (rgb_color.b.g * 0.686) +
		(rgb_color.b.b * 0.168));
	sepia.b.b = (unsigned char)((rgb_color.b.r * 0.272) + (rgb_color.b.g * 0.534) +
		(rgb_color.b.b * 0.131));
	return (sepia);
}

void			color_standard(t_env *env, t_double3 color, int *xy, int index)
{
	t_color		rgb_color;
	int			r;
	int			g;
	int			b;

	rgb_color.b.a = 0x00;
	rgb_color.b.r = (unsigned char)(255 * max_double(0, min_double(1, color.x)));
	rgb_color.b.g = (unsigned char)(255 * max_double(0, min_double(1, color.y)));
	rgb_color.b.b = (unsigned char)(255 * max_double(0, min_double(1, color.z)));
	if (env->scene->sepia)
		rgb_color = sepia(rgb_color);
	if (env->scene->neg)
	{
		rgb_color.b.r = 255 - rgb_color.b.r;
		rgb_color.b.g = 255 - rgb_color.b.g;
		rgb_color.b.b = 255 - rgb_color.b.b;
	}
	color_pixel_image(rgb_color, (WIDTH * xy[1] + xy[0]) * env->img[index]->opp,
		env->img[index]);
}
