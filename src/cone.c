/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:02:50 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 20:04:59 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static int			intersect_cone(t_vector ray, t_object *cone,
	t_double2 *distance)
{
	double			angle;
	double			a;
	double			b;
	double			c;

	angle = cone->radius * (M_PI / 180.0);
	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y -
		(ray.dir.z * ray.dir.z) * angle;
	b = 2 * (ray.pos.x * ray.dir.x + ray.pos.y *
		ray.dir.y - ray.pos.z * ray.dir.z * angle);
	c = ray.pos.x * ray.pos.x + ray.pos.y * ray.pos.y -
		ray.pos.z * ray.pos.z * angle;
	if (solve_quadratic(a, b, c, distance))
		return (1);
	return (0);
}

void				get_nearest_cone(t_vector ray, t_object *cone,
	t_surface *surface, t_scene *scene)
{
	t_double2			distance;
	t_surface			*tmp;
	t_vector			ray_s;

	ray_s = transform_ray(ray, cone);
	if (intersect_cone(ray_s, cone, &distance))
	{
		tmp = cut_object(ray, cone, distance, scene);
		if (tmp->object != NULL && (surface->distance == -1 ||
			surface->distance > tmp->distance))
		{
			surface->object = tmp->object;
			surface->distance = tmp->distance;
			surface->normal = tmp->normal;
			surface->color = tmp->object->color;
			if (tmp->object->texture != NULL)
				surface->color = cylindrical_mapping(surface, ray_s, cone);
			free(tmp);
		}
	}
}
