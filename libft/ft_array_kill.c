/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_kill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 22:00:54 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 22:27:32 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_array_kill(void *array, void (*f)(void *data))
{
	if (f != NULL)
		ft_array_clr((t_array*)array, f);
	if (array != NULL)
	{
		if (((t_array*)array)->data != NULL)
			free(((t_array*)array)->data);
		free(array);
	}
}
