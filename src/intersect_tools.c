/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:02:50 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 20:06:13 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

t_vector		transform_ray(t_vector ray, t_object *object)
{
	t_vector	new_ray;

	new_ray.pos = v_minus_v(ray.pos, object->pos);
	new_ray.pos = rotation(new_ray.pos, object->rotation, INVERSE_MATRIX);
	new_ray.dir = rotation(ray.dir, object->rotation, INVERSE_MATRIX);
	return (new_ray);
}

int				solve_quadratic(double a, double b, double c,
	t_double2 *distance)
{
	double		delta;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	distance->x = (-b - sqrt(delta)) / (2 * a);
	distance->y = (-b + sqrt(delta)) / (2 * a);
	if (distance->x < 0 && distance->y < 0)
		return (0);
	return (1);
}

void			swap(double *t0, double *t1)
{
	double tmp;

	tmp = *t0;
	*t0 = *t1;
	*t1 = tmp;
}
