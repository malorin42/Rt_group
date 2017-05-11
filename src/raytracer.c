/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 19:52:43 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 20:07:17 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

t_surface			*is_in_light(t_surface *surface, t_scene *scene,
	t_light *light, double *dot_light)
{
	t_vector		light_ray;
	t_double3		light_distance;
	t_surface		*light_intersect;
	double			dot_light_dir;

	light_ray.pos = surface->point;
	light_distance = v_minus_v(light->pos, surface->point);
	light_ray.dir = normalize(light_distance);
	*dot_light = dot_product(light_ray.dir, surface->normal);
	*dot_light = max_double(0, *dot_light);
	if (length_v(light->dir) > 0.01)
	{
		dot_light_dir = abs_double(dot_product(light_ray.dir,
			normalize(light->dir)));
		dot_light_dir = max_double(0, dot_light_dir);
		*dot_light *= dot_light_dir;
	}
	if (scene->cell_shading)
		cel_shading(dot_light);
	light_intersect = intersect(light_ray, scene, surface->object);
	if (light_intersect->object != NULL)
		light_intersect->distance -= length_v(light_distance);
	return (light_intersect);
}

t_double3			specular(t_surface *surface, t_light *light,
	t_vector ray, t_double3 color_hit)
{
	t_double3		specular_color;

	if (surface->object->type != PLANE)
	{
		specular_color = scale_v(light->color,
			pow(max_double(0, -dot_product(reflect(scale_v(
				normalize(v_minus_v(light->pos, surface->point)), -1),
			surface->normal), ray.dir)), 50));
		specular_color = scale_v(specular_color, 2);
	}
	else
		specular_color = scale_v(light->color,
			pow(max_double(0, -dot_product(reflect(scale_v(
				normalize(v_minus_v(light->pos, surface->point)), -1),
			surface->normal), ray.dir)), 150));
	color_hit = v_plus_v(color_hit, specular_color);
	return (color_hit);
}

t_double3			color_diffused(t_scene *scene, t_surface *surface,
	t_vector ray)
{
	t_double3		color_hit;
	t_light			*light;
	int				light_nb;
	double			dot_light;
	t_surface		*light_intersect;

	color_hit = (t_double3){0, 0, 0};
	light = scene->light;
	light_nb = 0;
	while (light)
	{
		light_intersect = is_in_light(surface, scene, light, &dot_light);
		if (light_intersect->object == NULL || light_intersect->distance > 0)
		{
			color_hit = v_plus_v(color_hit, color_mix(scale_v(light->color,
	dot_light), surface->object->gloss, scale_v(surface->color, dot_light)));
			color_hit = specular(surface, light, ray, color_hit);
		}
		free(light_intersect);
		light_nb++;
		light = light->next;
	}
	if (light_nb > 1)
		color_hit = scale_v(color_hit, (1.0 / (double)light_nb));
	return (color_hit);
}

t_double3			direct_light(t_vector ray, t_scene *scene,
	t_double3 color_hit)
{
	t_light			*light;
	t_double3		light_vector;
	t_surface		*light_intersect;
	double			dot_light;

	light = scene->light;
	while (light)
	{
		light_vector = v_minus_v(light->pos, ray.pos);
		dot_light = dot_product(normalize(light_vector), ray.dir);
		dot_light = max_double(0, exp(dot_light + 7.51745) - 5000);
		light_intersect = intersect((t_vector){scene->camera.pos,
			normalize(light_vector)}, scene, NULL);
		if (light_intersect->object == NULL || (light_intersect->distance >
			length_v(light_vector)))
			color_hit = color_mix(light->color, dot_light, color_hit);
		free(light_intersect);
		light = light->next;
	}
	return (color_hit);
}

t_double3			raytracer(t_vector ray, t_scene *scene,
	t_object *to_ignore, int depth)
{
	t_surface		*surface;
	t_double3		color_hit;

	if (depth == DEPTH_MAX)
		color_hit = (t_double3){0, 0, 0};
	surface = intersect(ray, scene, to_ignore);
	if (surface->object == NULL)
		color_hit = (t_double3){0, 0, 0};
	else
	{
		color_hit = (t_double3){0, 0, 0};
		color_hit = color_mix(surface->color, scene->ambiant,
			color_diffused(scene, surface, ray));
		if (surface->object->reflex > 0.01)
			color_hit = color_mix(color_reflected(ray, scene, surface, depth),
				surface->object->reflex, color_hit);
		if (surface->object->transparency > 0.01)
			color_hit = color_mix(color_refracted(ray, scene, surface, depth),
				surface->object->transparency, color_hit);
	}
	if (scene->direct_light)
		color_hit = direct_light(ray, scene, color_hit);
	free(surface);
	return (color_hit);
}
