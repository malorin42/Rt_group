/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_addn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 22:00:54 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 22:29:52 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_tab_addn(t_tab *tab, const void *add, int n)
{
	const int	bytes = tab->size * n;

	if (!ft_tab_ext(tab, n))
		return ;
	ft_memmove(tab->data + tab->bytes, add, bytes);
	tab->length += n;
	tab->bytes += bytes;
}
