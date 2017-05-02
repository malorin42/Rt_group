#include "../rtv1.h"

int				is_between_cuts(t_double3 point, t_object *object)
{
	if (point.x < object->dcp_x.x || point.x > object->dcp_x.y ||
		point.y < object->dcp_y.x || point.y > object->dcp_y.y ||
		point.z < object->dcp_z.x || point.z > object->dcp_z.y)
		return (0);
	return(1);
}

t_surface		*cut_object(t_vector ray, t_object *object, t_double2 *distance)
{
	double		distance_cut;
	t_surface	*tmp;

	tmp = (t_surface*)malloc(sizeof(t_surface));
	tmp->distance = -1;
	if (distance->x > 0 && is_between_cuts(find_point(ray.pos, ray.dir, distance->x), object))
	{
		tmp->distance = distance->x;
		tmp->normal = get_normal(object, find_point(ray.pos, ray.dir, tmp->distance));
	}
	if (distance->y > 0 && is_between_cuts(find_point(ray.pos, ray.dir, distance->y), object))
	{
		tmp->distance = min_positive(distance->y, tmp->distance);
		tmp->normal = get_normal(object, find_point(ray.pos, ray.dir, tmp->distance));
	}
	tmp->object = (tmp->distance > 0 ? object : NULL);
	return (tmp);
}