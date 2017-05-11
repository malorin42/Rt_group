/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_space_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 16:13:40 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 16:05:20 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static int		pars_value(t_env *env, t_pars *pars, t_buff line, int i)
{
	t_double3	values;
	int			nbr;

	if (i == 1 || i == 2 || i == 7)
		nbr = 3;
	else if (i == 3)
		nbr = 1;
	else if (i == 4 || i == 5 || i == 6)
		nbr = 2;
	if (check_pars_nbr_value(env, pars, line, nbr) == 1)
	{
		values = pick_values(line, nbr);
		if (pars->balise == 1)
			add_value(env, &values, i);
		else if (pars->balise == 2)
			add_light_value(env, &values, i);
		else if (pars->balise == 5)
			add_value_neg(env, &values, i);
		else if (pars->balise == 4)
			add_camera_value(env, &values, i);
		return (1);
	}
	return (0);
}

static int		lookat_decoupe(t_pars *pars, char *type, t_buff line)
{
	char		*dcp;
	int			i;
	int			ret;

	i = 0;
	dcp = "Decoupe\0";
	if (ft_strstr(type, "Decoupe") == NULL)
		return (0);
	while (type[i] != '\0' && dcp[i] != '\0' && type[i] == dcp[i])
		i++;
	if (type[i] != '.')
	{
		i = pars_error(pars, "Error : Decoupe need a X/Y/Z value name.",
			line.data);
		return (i);
	}
	i++;
	if (type[i] == 'X' || type[i] == 'Y' || type[i] == 'Z' ||
		type[i + 1] == '\0')
		i = is_type_xyz(type, i);
	else
		return (pars_error(pars, "Error : Not a X/Y/Z value name.", line.data));
	return (i);
}

static int		lookat_type_condition(t_env *env, t_pars *pars,
	t_buff line, char *type)
{
	int			i;

	if (ft_strcmp(type, "Pos") == 0 && pars->i_pos == 0)
		return (1);
	else if ((!ft_strcmp(type, "Rot") || !ft_strcmp(type, "Dir")) &&
		pars->i_dir == 0)
		return (2);
	else if (ft_strcmp(type, "Radius") == 0 && pars->i_radius == 0)
		return (3);
	else if ((i = lookat_decoupe(pars, type, line)) != 0 &&
		pars->i_dcp < 2 && pars->dcp == 1)
		return (i);
	else if (ft_strcmp(type, "Rot_text") == 0 && pars->texture == 1)
		return (7);
	else
		return (pars_error(pars, "Error : Unknow Value Name.", line.data));
}

static void		incr_i_type(t_pars *pars, int i)
{
	if (i == 1)
		pars->i_pos++;
	else if (i == 2)
		pars->i_dir++;
	else if (i == 3)
		pars->i_radius++;
	else if (i == 4)
		pars->i_dcp++;
}

void			pars_in_balise(t_env *env, t_pars *pars, t_buff line)
{
	char		*type;
	int			i;

	i = 0;
	type = check_line_type(env, pars, line);
	if (type != NULL)
	{
		if ((i = lookat_type_condition(env, pars, line, type)) != 0)
		{
			if (pars_value(env, pars, line, i) == 1)
				incr_i_type(pars, i);
		}
	}
}
