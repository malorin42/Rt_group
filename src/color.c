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

static void			sepia(t_color rgb_color, int *r, int *g, int *b)
{
	*r = (int)(rgb_color.b.r * 0.393) + (rgb_color.b.g * 0.769) +
		(rgb_color.b.b * 0.189);
	*g = (int)(rgb_color.b.r * 0.349) + (rgb_color.b.g * 0.686) +
		(rgb_color.b.b * 0.168);
	*b = (int)(rgb_color.b.r * 0.272) + (rgb_color.b.g * 0.534) +
		(rgb_color.b.b * 0.131);
}

void			color_standard(t_env *env, t_double3 color, int *xy, int index)
{
	t_color		rgb_color;
	int			r;
	int			g;
	int			b;

	rgb_color.b.a = 0x00;
	r = 255 * max_double(0, min_double(1, color.x));
	g = 255 * max_double(0, min_double(1, color.y));
	b = 255 * max_double(0, min_double(1, color.z));
	rgb_color.b.r = r;
	rgb_color.b.g = g;
	rgb_color.b.b = b;
	if (env->scene->sepia)
		sepia(rgb_color, &r, &g ,&b);
	if (env->scene->neg)
	{
		r = 255 - r;
		g = 255 - g;
		b = 255 - b;
	}
	rgb_color.b.r = r;
	rgb_color.b.g = g;
	rgb_color.b.b = b;
	color_pixel_image(rgb_color, (WIDTH * xy[1] + xy[0]) * env->img[index]->opp,
		env->img[index]);
}
