/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 18:39:33 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 20:06:44 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void			light_add(t_light **first, t_light *new)
{
	new->next = *first;
	*first = new;
}

void			neg_obj_add(t_negobj **first, t_negobj *new)
{
	new->next = *first;
	*first = new;
}

void			object_add(t_object **first, t_object *new)
{
	new->next = *first;
	*first = new;
}
