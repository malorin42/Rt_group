/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_ini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 22:00:54 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 22:30:02 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_tab_ini(t_tab *tab, int size)
{
	tab->data = (unsigned char*)malloc(sizeof(unsigned char) * (size * 16));
	tab->length = 0;
	tab->bytes = 0;
	tab->alloc_bytes = (tab->data == NULL) ? 0 : 16;
	tab->size = size;
}
