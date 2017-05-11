/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 16:13:40 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 20:04:22 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

int			add_on_off_value(t_object **object,
	char *value, t_pars *pars, t_buff line)
{
	t_object	*tmp;

	tmp = *object;
	if (strcmp(value, "On") == 0)
	{
		tmp->dcp = 1;
		return (1);
	}
	else if (strcmp(value, "Off") == 0)
	{
		tmp->dcp = 0;
		return (0);
	}
	else
		pars_error(pars, "Error : Wrong Off/On Value.", line.data);
	return (0);
}

static int	search_param(char *line, char *type)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		while (line[i] != '\0' && line[i] != '\n' && line[i] == type[j])
		{
			i++;
			j++;
			if (type[j] == '\0')
				return (i + 1);
		}
		j = 0;
		i++;
	}
	return (-1);
}

void		add_double_param(t_buff line, char *type, t_object **object,
	char *value)
{
	t_object	*tmp;

	tmp = *object;
	line.i = search_param(line.data, type);
	if (ft_strcmp(type, "gloss") == 0)
		tmp->gloss = max_double(0, min_double(1, ft_parse_double(&line)));
	else if (ft_strcmp(type, "transp") == 0)
		tmp->transparency = max_double(0, min_double(1,
			ft_parse_double(&line)));
	else if (ft_strcmp(type, "refraction") == 0)
		tmp->refraction = max_double(1, ft_parse_double(&line));
	else if (ft_strcmp(type, "reflex") == 0)
		tmp->reflex = max_double(0, min_double(1, ft_parse_double(&line)));
}
