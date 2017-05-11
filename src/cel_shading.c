/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cel_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 12:43:45 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 20:04:32 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void	cel_shading(double *dot_light)
{
	if (*dot_light < 0.2)
		*dot_light = 0;
	else if (*dot_light >= 0.2 && *dot_light < 0.4)
		*dot_light = 0.2;
	else if (*dot_light >= 0.4 && *dot_light < 0.5)
		*dot_light = 0.4;
	else if (*dot_light >= 0.5)
		*dot_light = 0.5;
}
