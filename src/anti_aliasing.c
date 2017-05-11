/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahus <jbahus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:09:07 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 19:31:38 by jbahus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static void				pixel_ray_init_aa_2(t_double3 *pixel_ray,
	double x, double y)
{
	double		aspect_ratio;
	double		scale;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	scale = tan((FOV * 0.5 * PI) / 180.0);
	pixel_ray->x = (2 * ((x) / (double)WIDTH) - 1) *
	aspect_ratio * scale;
	pixel_ray->y = (1 - 2 * (y) / (double)HEIGHT) * scale;
}

static t_double3		pixel_ray_init_aa_1(t_double3 camera_dir,
	int x, int y, int i)
{
	t_double3	pixel_ray;

	if (i == 0)
		pixel_ray_init_aa_2(&pixel_ray, x + 0.25, y + 0.25);
	else if (i == 1)
		pixel_ray_init_aa_2(&pixel_ray, x + 0.75, y + 0.25);
	else if (i == 2)
		pixel_ray_init_aa_2(&pixel_ray, x + 0.25, y + 0.75);
	else if (i == 3)
		pixel_ray_init_aa_2(&pixel_ray, x + 0.75, y + 0.75);
	pixel_ray.z = -1;
	pixel_ray = normalize(pixel_ray);
	pixel_ray = rotation(pixel_ray, camera_dir, REGULAR_MATRIX);
	return ((t_double3)pixel_ray);
}

t_double3				aa(t_env *env, t_double3 color, int *xy, int *i)
{
	t_double3	pixel_ray;

	pixel_ray = pixel_ray_init_aa_1(env->scene->camera.dir, xy[0],
	xy[1] + ((HEIGHT / THREAD) * (i[1])), i[0]);
	color = v_plus_v(color, raytracer((t_vector){env->scene->camera.pos,
	pixel_ray}, env->scene, NULL, 0));
	color = scale_v(color, 0.50);
	return (color);
}
