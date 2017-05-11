/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pars_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 16:13:40 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 20:04:26 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void		add_camera_value(t_env *env, t_double3 *values, int i)
{
	if (i == 1)
		env->scene->camera.pos = *values;
	else if (i == 2)
		env->scene->camera.dir = *values;
}

void		add_light_value(t_env *env, t_double3 *values, int i)
{
	t_light	*tmp;

	tmp = env->scene->light;
	if (i == 1)
		tmp->pos = *values;
	else if (i == 2)
		tmp->dir = *values;
}

void		add_value_neg(t_env *env, t_double3 *values, int i)
{
	t_negobj	*tmp;

	tmp = env->scene->negobj;
	if (i == 1)
		tmp->pos = *values;
	else if (i == 2)
		tmp->rotation = *values;
	else if (i == 3)
		tmp->radius = values->x;
}

static void	add_value2(t_object *tmp, t_double3 *values, int i)
{
	if (i == 6)
	{
		tmp->dcp_z.x = values->x;
		tmp->dcp_z.y = values->y;
	}
	else if (i == 7)
		tmp->text_rot = *values;
}

void		add_value(t_env *env, t_double3 *values, int i)
{
	t_object	*tmp;

	tmp = env->scene->object;
	if (i == 1)
		tmp->pos = *values;
	else if (i == 2)
		tmp->rotation = *values;
	else if (i == 3)
		tmp->radius = values->x;
	else if (i == 4)
	{
		tmp->dcp_x.x = values->x;
		tmp->dcp_x.y = values->y;
	}
	else if (i == 5)
	{
		tmp->dcp_y.x = values->x;
		tmp->dcp_y.y = values->y;
	}
	add_value2(tmp, values, i);
}
