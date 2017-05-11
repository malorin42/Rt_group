/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_head_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:54:50 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 16:10:46 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static int		pars_offon_line(t_pars *pars, t_buff line)
{
	char	*str;
	int		i;

	str = ft_strnew(4);
	i = 0;
	ft_parse_not(&line, "<");
	while (line.data[line.i] != '\0' && line.data[line.i] != '>')
		line.i++;
	ft_parse_not(&line, "O");
	while (line.data[line.i] != '\0' && line.data[line.i] != ';')
	{
		str[i] = line.data[line.i];
		i++;
		line.i++;
	}
	str[i] = '\0';
	if (ft_strcmp(str, "ON") == 0)
		i = 1;
	else if (ft_strcmp(str, "OFF") == 0)
		i = 0;
	else
		return (pars_error(pars, "Error : Not a ON/OFF value.", line.data));
	free(str);
	return (i);
}

static void		incr_i_headtype(t_pars *pars, int i)
{
	if (i == 1)
		pars->i_ambiant++;
	else if (i == 2)
		pars->i_aliai++;
	else if (i == 3)
		pars->i_dir_light++;
	else if (i == 4)
		pars->i_sepia++;
	else if (i == 5)
		pars->i_negative++;
}

static void		pars_head_value(t_env *env, t_pars *pars, t_buff line, int i)
{
	t_double3	values;

	if (i == 1)
	{
		if (check_pars_nbr_value(env, pars, line, 1) == 1)
		{
			values = pick_values(line, 1);
			env->scene->ambiant = values.x;
			incr_i_headtype(pars, i);
		}
		return ;
	}
	else if (i == 2)
		env->scene->aliaising = pars_offon_line(pars, line);
	else if (i == 3)
		env->scene->direct_light = pars_offon_line(pars, line);
	else if (i == 4)
		env->scene->sepia = pars_offon_line(pars, line);
	else if (i == 5)
		env->scene->neg = pars_offon_line(pars, line);
	else if (i == 6)
		env->scene->cell_shading = pars_offon_line(pars, line);
	incr_i_headtype(pars, i);
}

static int		lookat_head_condition(t_env *env, t_pars *pars, t_buff line,
	char *type)
{
	printf("%d\n", pars->i_dir_light);
	if (ft_strcmp(type, "Ambiant") == 0 && pars->i_ambiant == 0)
		return (1);
	else if (ft_strcmp(type, "Aliasing") == 0 && pars->i_aliai == 0)
		return (2);
	else if (ft_strcmp(type, "Dir_light") == 0 && pars->i_dir_light == 0)
		return (3);
	else if (ft_strcmp(type, "Sepia") == 0 && pars->i_sepia == 0)
		return (4);
	else if (ft_strcmp(type, "Negative") == 0 && pars->i_negative == 0)
		return (5);
	else if (ft_strcmp(type, "Cartoon") == 0)
		return (6);
	else
		return (pars_error(pars, "Error : Unknow Head Value Name.", line.data));
}

void			pars_head_balise(t_env *env, t_pars *pars, t_buff line)
{
	char		*type;
	int			i;

	type = check_line_type(env, pars, line);
	if (type != NULL)
	{
		if ((i = lookat_head_condition(env, pars, line, type)) != 0)
			pars_head_value(env, pars, line, i);
	}
}
