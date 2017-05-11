/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 22:00:54 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 22:26:00 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_array_add(t_array *array, void *add)
{
	if (!ft_array_ext(array, 1))
		return ;
	array->data[array->length] = add;
	array->length++;
}
