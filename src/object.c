/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 18:39:14 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 20:06:40 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

t_light			*light_new(t_env *env, t_pars *pars, t_buff line)
{
	t_light		*light;

	if ((light = (t_light*)malloc(sizeof(t_light))) == NULL)
		ft_error("Error : malloc() failed.\n");
	if (open("./texture/light.xpm", O_RDONLY) < 0)
	{
		light->texture = NULL;
		pars_error(pars, "Error : No texture.xpm for light.", line.data);
	}
	else
		light->texture = init_texture(env->mlx, "./texture/light.xpm");
	light->pos = (t_double3){0, 0, 0};
	light->dir = (t_double3){0, 0, 0};
	light->color = (t_double3){0, 0, 0};
	return (light);
}

t_negobj		*neg_obj_new(void)
{
	t_negobj	*object;

	if ((object = (t_negobj*)malloc(sizeof(t_negobj))) == NULL)
		ft_error("Error : malloc() failed.\n");
	object->pos = (t_double3){0, 0, 0};
	object->rotation = (t_double3){0, 0, 0};
	object->radius = 0;
	return (object);
}

t_object		*object_new(int type)
{
	t_object	*object;

	if ((object = (t_object*)malloc(sizeof(t_object))) == NULL)
		ft_error("Error : malloc() failed.\n");
	object->texture = NULL;
	object->type = type;
	object->pos = (t_double3){0, 0, 0};
	object->rotation = (t_double3){0, 0, 0};
	object->text_rot = (t_double3){0, 0, 0};
	object->radius = 0;
	object->dcp_x = (t_double2){0, 0};
	object->dcp_y = (t_double2){0, 0};
	object->dcp_z = (t_double2){0, 0};
	object->color = (t_double3){1, 1, 1};
	object->reflex = 0;
	object->transparency = 0;
	object->gloss = 0;
	object->refraction = 1.2;
	object->perturbation = 0;
	object->next = NULL;
	object->dcp = 0;
	return (object);
}
