#include "../rtv1.h"

void		add_light_value(t_light **light, t_double3 *values, int i)
{
	t_light	*tmp;

	tmp = *light;
	if (i == 0)
		tmp->pos = *values;
	else if (i == 1)
		tmp->dir = *values;
}

void		add_value(t_object **object, t_double3 *values, int i)
{
	t_object	*tmp;

	tmp = *object;
	if (i == 0)
		tmp->pos = *values;
	else if (i == 1)
		tmp->rotation = *values;
	else if (i == 2)
		tmp->radius = values->x;
}
