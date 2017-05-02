#include "../rtv1.h"

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
	t_surface *surface)
{
	t_double2			distance;
	t_surface			*tmp;

	ray = transform_ray(ray, cone);
	if (intersect_cone(ray, cone, &distance))
	{
		if (cone->dcp)
		{
			tmp = cut_object(ray, cone, &distance);
			if (tmp->object != NULL && (surface->distance == -1 || surface->distance > tmp->distance))
			{
				surface->object = tmp->object;
				surface->distance = tmp->distance;
				surface->normal = tmp->normal;
				free(tmp);
			}
		}
		else if (surface->distance == -1 || surface->distance > min_positive(distance.x, distance.y))
		{
			surface->object = cone;
			surface->distance = min_positive(distance.x, distance.y);
			surface->normal = get_normal(cone, find_point(ray.pos, ray.dir, surface->distance));
		}
	}
}
