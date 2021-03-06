/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:02:50 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 20:07:37 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static t_double3	rotation_x(t_double3 point, double angle, int inverse)
{
	t_double3	new_point;

	if (abs_double(angle) < 0.00001)
		return (point);
	angle = angle * (PI / 180.0);
	new_point.x = point.x;
	new_point.y = point.y * cos(angle) - point.z * sin(angle) * inverse;
	new_point.z = point.y * sin(angle) * inverse + point.z * cos(angle);
	return (new_point);
}

static t_double3	rotation_y(t_double3 point, double angle, int inverse)
{
	t_double3	new_point;

	if (abs_double(angle) < 0.00001)
		return (point);
	angle = angle * (PI / 180.0);
	new_point.x = point.x * cos(angle) + point.z * sin(angle) * inverse;
	new_point.y = point.y;
	new_point.z = -point.x * sin(angle) * inverse + point.z * cos(angle);
	return (new_point);
}

static t_double3	rotation_z(t_double3 point, double angle, int inverse)
{
	t_double3	new_point;

	if (abs_double(angle) < 0.00001)
		return (point);
	angle = angle * (PI / 180.0);
	new_point.x = point.x * cos(angle) - point.y * sin(angle) * inverse;
	new_point.y = point.x * sin(angle) * inverse + point.y * cos(angle);
	new_point.z = point.z;
	return (new_point);
}

t_double3			rotation(t_double3 point, t_double3 angles, int inverse)
{
	if (inverse == INVERSE_MATRIX)
	{
		point = rotation_x(point, angles.x, inverse);
		point = rotation_y(point, angles.y, inverse);
		point = rotation_z(point, angles.z, inverse);
	}
	else
	{
		point = rotation_z(point, angles.z, inverse);
		point = rotation_y(point, angles.y, inverse);
		point = rotation_x(point, angles.x, inverse);
	}
	return (point);
}
