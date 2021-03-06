/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:02:50 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 20:07:25 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static t_double3	refract(t_double3 incidence, t_double3 normal, double ior)
{
	t_double3		refract;
	double			dot_incidence;

	ior = 1 / ior;
	dot_incidence = dot_product(incidence, normal);
	refract.x = ior * incidence.x + (ior * dot_incidence -
		sqrt(1 + ior * ior * (dot_incidence * dot_incidence - 1))) * normal.x;
	refract.y = ior * incidence.y + (ior * dot_incidence -
		sqrt(1 + ior * ior * (dot_incidence * dot_incidence - 1))) * normal.y;
	refract.z = ior * incidence.z + (ior * dot_incidence -
		sqrt(1 + ior * ior * (dot_incidence * dot_incidence - 1))) * normal.z;
	return (normalize(refract));
}

t_double3			color_refracted(t_vector ray, t_scene *scene,
	t_surface *surface, int depth)
{
	t_double3		refracted_ray;
	t_double3		refracted_color;

	refracted_ray = refract(ray.dir, surface->normal,
		surface->object->refraction);
	refracted_color = raytracer((t_vector){surface->point, refracted_ray},
		scene, surface->object, depth + 1);
	refracted_color.x = max_double(0, min_double(1, refracted_color.x));
	refracted_color.y = max_double(0, min_double(1, refracted_color.y));
	refracted_color.z = max_double(0, min_double(1, refracted_color.z));
	return (refracted_color);
}
