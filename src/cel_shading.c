/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cel_shading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahus <jbahus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 12:43:45 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/09 12:43:55 by jbahus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

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
