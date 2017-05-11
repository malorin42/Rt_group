/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_ini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 22:00:54 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 22:26:15 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_array_ini(t_array *array)
{
	array->data = (void**)malloc(sizeof(void*) * 16);
	if (array->data != NULL)
		ft_bzero(array->data, 16);
	array->length = 0;
	array->alloc_length = (array->data == NULL) ? 0 : 16;
}
