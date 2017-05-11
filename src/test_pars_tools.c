/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pars_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 16:13:40 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 20:07:56 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static int		search_next_nbr(t_buff line, int i)
{
	while (line.data[i] != '\0' && line.data[i] != '\n' &&
		ft_isdigit(line.data[i]) == 0)
		i++;
	if (ft_isdigit(line.data[i]) == 0)
		i = -1;
	return (i);
}

t_double3		pick_values(t_buff line, int nbr)
{
	t_double3	values;

	values.x = 0;
	values.y = 0;
	values.z = 0;
	ft_parse_not(&line, "{");
	line.i++;
	if (nbr >= 1)
		values.x = ft_parse_double(&line);
	if (nbr >= 2)
	{
		ft_parse_not(&line, "-0123456789");
		values.y = ft_parse_double(&line);
	}
	if (nbr == 3)
	{
		ft_parse_not(&line, "-0123456789");
		values.z = ft_parse_double(&line);
	}
	return (values);
}

int				check_object_type(t_env *env, char *type,
	t_pars *pars, t_buff line)
{
	if (ft_strcmp(type, "Sphere") == 0)
		init_object(env, pars, SPHERE, &env->scene->object);
	else if (ft_strcmp(type, "Plane") == 0)
		init_object(env, pars, PLANE, &env->scene->object);
	else if (ft_strcmp(type, "Cylinder") == 0)
		init_object(env, pars, CYLINDER, &env->scene->object);
	else if (ft_strcmp(type, "Cone") == 0)
		init_object(env, pars, CONE, &env->scene->object);
	else
		return (pars_error(pars, "Error : Wrong object type.", line.data));
	return (1);
}

static int		check_pars_nbr_value2(t_env *env, t_pars *pars,
	char *line, int i)
{
	while (ft_isdigit(line[i]) == 1)
		i++;
	if (line[i] != '.' && line[i] != '}')
		pars_error(pars, "Error : Problem in Bracket.", line);
	else
		i++;
	while (ft_isdigit(line[i]) == 1)
		i++;
	return (i);
}

int				check_pars_nbr_value(t_env *env, t_pars *pars,
	t_buff line, int nbr)
{
	int		i;

	i = 0;
	while (line.data[i] != '{' && line.data[i] != '\0')
		i++;
	if (line.data[i] != '{')
		pars_error(pars, "Error : Bracket Problem.", line.data);
	while (line.data[++i] != '\0')
	{
		if (ft_isdigit(line.data[i]) == 1)
		{
			i = check_pars_nbr_value2(env, pars, line.data, i);
			if (ft_isspace(line.data[i]) == 1 || line.data[i] == '}')
				nbr--;
			else
				pars_error(pars, "Error : Problem in Bracket.", line.data);
		}
	}
	if (nbr > 0 || nbr < 0)
	{
		i = pars_error(pars,
		"Error : Wrong Numbers of Values in a Line.", line.data);
		return (i);
	}
	return (1);
}
