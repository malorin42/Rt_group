/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:02:50 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/12 00:43:21 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static t_double3	get_color_from_texture(t_image *texture, t_double2 map)
{
	t_double3		color;
	int				pixel_start;

	map.y = 1 - map.y;
	pixel_start = ((texture->width * (int)(map.y * texture->height) +
		(int)(map.x * texture->width)) * texture->opp);
	color.z = (double)((unsigned char)texture->data[pixel_start] / 255.0);
	color.y = (double)((unsigned char)texture->data[pixel_start + 1] / 255.0);
	color.x = (double)((unsigned char)texture->data[pixel_start + 2] / 255.0);
	return (color);
}

t_double3			planar_mapping(t_surface *surface, t_vector ray,
	t_object *object)
{
	t_double2		map;
	t_double3		point;

	point = find_point(ray.pos, ray.dir, surface->distance);
	if (object->dcp)
	{
		map.x = (point.x - object->dcp_x.x) /
		(object->dcp_x.y - object->dcp_x.x);
		map.y = (point.y - object->dcp_y.x) /
		(object->dcp_y.y - object->dcp_y.x);
	}
	else
	{
		map.x = fmod(abs_double(point.x), (object->texture->width / 100.0)) /
		(object->texture->width / 100.0);
		map.y = fmod(abs_double(point.y), (object->texture->height / 100.0)) /
		(object->texture->height / 100.0);
	}
	return (get_color_from_texture(object->texture, map));
}

t_double3			spherical_mapping(t_surface *surface, t_vector ray,
	t_object *object)
{
	t_double3		ve;
	t_double3		vn;
	t_double3		vp;
	double			theta;
	t_double2		map;

	ve = rotation((t_double3){0, 1, 0}, object->text_rot, REGULAR_MATRIX);
	vn = rotation((t_double3){0, 0, 1}, object->text_rot, REGULAR_MATRIX);
	vp = normalize(find_point(ray.pos, ray.dir, surface->distance));
	theta = acos(dot_product(vp, ve) / sin(acos(-dot_product(vn, vp)))) /
	(2 * PI);
	map.y = acos(-dot_product(vn, vp)) / PI;
	if (dot_product(cross_product(vn, ve), vp) > 0)
		map.x = theta;
	else
		map.x = 1 - theta;
	return (get_color_from_texture(object->texture, map));
}

t_double3			cylindrical_mapping(t_surface *surface, t_vector ray,
	t_object *object)
{
	t_double3		ve;
	t_double3		vn;
	t_double3		vp;
	double			theta;
	t_double2		map;

	ve = rotation((t_double3){0, 1, 0}, object->text_rot, REGULAR_MATRIX);
	vn = rotation((t_double3){0, 0, 1}, object->text_rot, REGULAR_MATRIX);
	vp = find_point(ray.pos, ray.dir, surface->distance);
	theta = acos(dot_product(ve, normalize((t_double3){vp.x, vp.y, 0}))) /
	(2 * PI);
	if (object->dcp)
		map.y = (vp.z - object->dcp_z.x) / (object->dcp_z.y - object->dcp_z.x);
	else
		map.y = fmod(abs_double(vp.z), (object->texture->height / 100.0)) /
	(object->texture->height / 100.0);
	if (dot_product(cross_product(vn, ve), vp) > 0)
		map.x = theta;
	else
		map.x = 1 - theta;
	return (get_color_from_texture(object->texture, map));
}
