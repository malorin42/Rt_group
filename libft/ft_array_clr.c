/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_clr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 22:26:36 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 22:26:48 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_array_clr(void *array, void (*f)(void *data))
{
	int			i;

	i = -1;
	if (f != NULL)
		while (++i < ((t_array*)array)->length)
			f(((t_array*)array)->data[i]);
	ft_bzero(((t_array*)array)->data, (sizeof(void*) *
		((t_array*)array)->length));
	((t_array*)array)->length = 0;
}
