/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflexion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:02:50 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 20:07:21 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

t_double3			reflect(t_double3 incidence, t_double3 normal)
{
	t_double3		reflect;

	reflect.x = incidence.x - 2 * dot_product(incidence, normal) * normal.x;
	reflect.y = incidence.y - 2 * dot_product(incidence, normal) * normal.y;
	reflect.z = incidence.z - 2 * dot_product(incidence, normal) * normal.z;
	return (normalize(reflect));
}

t_double3			color_reflected(t_vector ray, t_scene *scene,
	t_surface *surface, int depth)
{
	t_double3		reflected_ray;
	t_double3		reflected_color;

	reflected_ray = reflect(ray.dir, surface->normal);
	reflected_color = raytracer((t_vector){surface->point, reflected_ray},
		scene, surface->object, depth + 1);
	return (reflected_color);
}
