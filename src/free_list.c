/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 22:12:26 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 22:22:12 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void	free_negobj(t_negobj *obj)
{
	if (obj->next)
		free_negobj(obj->next);
	free(obj);
}

void	free_obj(t_object *obj)
{
	if (obj->next)
		free_obj(obj->next);
	free(obj->texture);
	free(obj);
}

void	free_light(t_light *light)
{
	if (light->next)
		free_light(light->next);
	free(light->texture);
	free(light);
}
