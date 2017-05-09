/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_pixel_image.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahus <jbahus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 12:42:18 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/09 12:44:21 by jbahus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void		color_pixel_image(t_color color, int pixel_start,
	t_image *image)
{
	int			pixel_end;

	pixel_end = pixel_start + image->opp;
	while (pixel_start < pixel_end)
	{
		image->data[pixel_start] = color.b.b;
		color.u >>= 8;
		pixel_start++;
	}
}
