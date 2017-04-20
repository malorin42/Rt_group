#include "../rtv1.h"

static int				intersect_cone(t_vector ray, t_object *cone, double *distance)
{
	double			angle;
	double			tan_squared;
	double			a;
	double			b;
	double			c;
	t_double3		test_limit;

	angle = cone->radius * (M_PI / 180.0);
	tan_squared = tan(angle) * tan(angle);
	a = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y -
		(ray.dir.z * ray.dir.z) * angle;
	b = 2 * (ray.pos.x * ray.dir.x + ray.pos.y *
		ray.dir.y - ray.pos.z * ray.dir.z * angle);
	c = ray.pos.x * ray.pos.x + ray.pos.y * ray.pos.y -
		ray.pos.z * ray.pos.z * angle;
	if (solve_quadratic(a, b, c, distance))
	{
		test_limit = find_point(ray.pos, ray.dir, *distance);
		if (test_limit.z > 0 && test_limit.z < 3)
			return (1);
	}
	return (0);
}

void				get_nearest_cone(t_vector ray, t_object *cone, t_surface **surface)
{
	double			distance;

	ray = transform_ray(ray, cone);
	if (intersect_cone(ray, cone, &distance))
	{
		if (*surface == NULL)
		{
			if ((*surface = (t_surface*)malloc(sizeof(t_surface))) == NULL)
				ft_error("Error : malloc() failed.\n");
			(*surface)->object = cone;
			(*surface)->distance = distance;
			(*surface)->simple = find_point(ray.pos, ray.dir, distance);
		}
		else if ((*surface)->distance > distance)
		{
			(*surface)->object = cone;
			(*surface)->distance = distance;
			(*surface)->simple = find_point(ray.pos, ray.dir, distance);
		}
	}
}