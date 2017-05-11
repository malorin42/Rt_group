/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 16:13:40 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 20:05:29 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static t_double3	reinit_double(void)
{
	t_double3	rgb;

	rgb.x = 1;
	rgb.y = 1;
	rgb.z = 1;
	return (rgb);
}

static t_double3	hex_to_double(t_buff line, t_pars *pars, char *str)
{
	char		*tmp;
	t_double3	rgb;
	double		hex[6];
	int			i;

	tmp = ft_strnew(ft_strlen(str));
	tmp = ft_strcpy(tmp, str);
	i = -1;
	while (tmp[++i] != '\0' && i < 6)
	{
		tmp[i] = ft_toupper(tmp[i]);
		if (tmp[i] >= 48 && tmp[i] <= 57)
			hex[i] = tmp[i] - 48;
		else if (tmp[i] >= 65 && tmp[i] <= 70)
			hex[i] = tmp[i] - 55;
		else
		{
			pars_error(pars, "Mauvais typage hexadecimal.", line.data);
			return (reinit_double());
		}
	}
	rgb.x = (hex[0] * 16 + hex[1]) / 255;
	rgb.y = (hex[2] * 16 + hex[3]) / 255;
	rgb.z = (hex[4] * 16 + hex[5]) / 255;
	return (rgb);
}

void				check_color_light(t_buff line, t_pars *pars,
	t_light **light, char *value)
{
	t_light		*tmp;

	tmp = *light;
	if (ft_strcmp(value, "red") == 0)
		tmp->color = hex_to_double(line, pars, RED);
	else if (ft_strcmp(value, "blue") == 0)
		tmp->color = hex_to_double(line, pars, BLUE);
	else if (ft_strcmp(value, "green") == 0)
		tmp->color = hex_to_double(line, pars, GREEN);
	else if (ft_strcmp(value, "lightblue") == 0)
		tmp->color = hex_to_double(line, pars, LIGHT_BLUE);
	else if (ft_strcmp(value, "lightgreen") == 0)
		tmp->color = hex_to_double(line, pars, LIGHT_GREEN);
	else if (ft_strcmp(value, "orange") == 0)
		tmp->color = hex_to_double(line, pars, ORANGE);
	else if (ft_strcmp(value, "pink") == 0)
		tmp->color = hex_to_double(line, pars, PINK);
	else if (ft_strcmp(value, "purple") == 0)
		tmp->color = hex_to_double(line, pars, PURPLE);
	else
		tmp->color = hex_to_double(line, pars, value);
	if (value != NULL)
		free(value);
}

void				check_color_obj(t_buff line, t_pars *pars,
	t_object **object, char *value)
{
	t_object	*tmp;

	tmp = *object;
	if (ft_strcmp(value, "red") == 0)
		tmp->color = hex_to_double(line, pars, RED);
	else if (ft_strcmp(value, "blue") == 0)
		tmp->color = hex_to_double(line, pars, BLUE);
	else if (ft_strcmp(value, "green") == 0)
		tmp->color = hex_to_double(line, pars, GREEN);
	else if (ft_strcmp(value, "lightblue") == 0)
		tmp->color = hex_to_double(line, pars, LIGHT_BLUE);
	else if (ft_strcmp(value, "lightgreen") == 0)
		tmp->color = hex_to_double(line, pars, LIGHT_GREEN);
	else if (ft_strcmp(value, "orange") == 0)
		tmp->color = hex_to_double(line, pars, ORANGE);
	else if (ft_strcmp(value, "pink") == 0)
		tmp->color = hex_to_double(line, pars, PINK);
	else if (ft_strcmp(value, "purple") == 0)
		tmp->color = hex_to_double(line, pars, PURPLE);
	else
		tmp->color = hex_to_double(line, pars, value);
	if (value != NULL)
		free(value);
}
