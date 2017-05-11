/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahus <jbahus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:09:07 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 14:36:40 by jbahus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static t_double3		pixel_ray_init_aa_2(t_double3 camera_dir,
	int x, int y, int i)
{
	t_double3	pixel_ray;
	double		aspect_ratio;
	double		scale;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	scale = tan((FOV * 0.5 * PI) / 180.0);
	if (i == 2)
	{
		pixel_ray.x = (2 * ((x + 0.25) / (double)WIDTH) - 1) *
		aspect_ratio * scale;
		pixel_ray.y = (1 - 2 * (y + 0.75) / (double)HEIGHT) * scale;
	}
	else if (i == 3)
	{
		pixel_ray.x = (2 * ((x + 0.75) / (double)WIDTH) - 1) *
		aspect_ratio * scale;
		pixel_ray.y = (1 - 2 * (y + 0.75) / (double)HEIGHT) * scale;
	}
	pixel_ray.z = -1;
	pixel_ray = normalize(pixel_ray);
	pixel_ray = rotation(pixel_ray, camera_dir, REGULAR_MATRIX);
	return (pixel_ray);
}

static t_double3		pixel_ray_init_aa_1(t_double3 camera_dir,
	int x, int y, int i)
{
	t_double3	pixel_ray;
	double		aspect_ratio;
	double		scale;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	scale = tan((FOV * 0.5 * PI) / 180.0);
	if (i == 0)
	{
		pixel_ray.x = (2 * ((x + 0.25) / (double)WIDTH) - 1) *
		aspect_ratio * scale;
		pixel_ray.y = (1 - 2 * (y + 0.25) / (double)HEIGHT) * scale;
	}
	else if (i == 1)
	{
		pixel_ray.x = (2 * ((x + 0.75) / (double)WIDTH) - 1) *
		aspect_ratio * scale;
		pixel_ray.y = (1 - 2 * (y + 0.25) / (double)HEIGHT) * scale;
	}
	pixel_ray = pixel_ray_init_aa_2(camera_dir, x, y, i);
	return (pixel_ray);
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
