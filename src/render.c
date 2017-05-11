/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahus <jbahus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:13:04 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 14:39:31 by jbahus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static t_double3		pixel_ray_init(t_double3 camera_dir, int x, int y)
{
	t_double3	pixel_ray;
	double		aspect_ratio;
	double		scale;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	scale = tan((FOV * 0.5 * PI) / 180.0);
	pixel_ray.x = (2 * ((x + 0.5) / (double)WIDTH) - 1) *
	aspect_ratio * scale;
	pixel_ray.y = (1 - 2 * (y + 0.5) / (double)HEIGHT) * scale;
	pixel_ray.z = -1;
	pixel_ray = normalize(pixel_ray);
	pixel_ray = rotation(pixel_ray, camera_dir, REGULAR_MATRIX);
	return (pixel_ray);
}

static void				init_index(void *env, int *index)
{
	pthread_mutex_lock(&((t_env*)env)->my_mutex);
	*index = ((t_env*)env)->count;
	pthread_cond_signal(&((t_env*)env)->cond);
	pthread_mutex_unlock(&((t_env*)env)->my_mutex);
}

static t_double3		aliasing(t_env *env, t_double3 color,
	int *xy, int index)
{
	t_double3	pixel_ray;

	pixel_ray = pixel_ray_init(env->scene->camera.dir, xy[0],
	xy[1] + ((HEIGHT / THREAD) * (index)));
	color = raytracer((t_vector){env->scene->camera.pos,
	pixel_ray}, env->scene, NULL, 0);
	return (color);
}

void					*render(void *env)
{
	t_double3	color;
	int			xy[2];
	int			i[2];

	init_index(env, &i[1]);
	xy[1] = 0;
	while (xy[1] < HEIGHT / THREAD)
	{
		xy[0] = 0;
		while (xy[0] < WIDTH)
		{
			i[0] = 0;
			while (i[0] < 4 && ((t_env*)env)->scene->aliaising)
			{
				color = aa(env, color, xy, i);
				i[0]++;
			}
			if (((t_env*)env)->scene->aliaising == 0)
				color = aliasing(env, color, xy, i[1]);
			color_standard((t_env*)env, color, xy, i[1]);
			xy[0]++;
		}
		xy[1]++;
	}
	pthread_exit(0);
}
