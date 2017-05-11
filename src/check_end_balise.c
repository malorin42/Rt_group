/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end_balise.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 21:24:05 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 20:05:33 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static int		end_balise(t_env *env, t_buff line, t_pars *pars)
{
	if (line.data[0] == '<')
	{
		if ((pars->balise == 1) && ft_strcmp(line.data, "<Object/>") == 0)
			return (1);
		else if ((pars->balise == 2) &&
			ft_strcmp(line.data, "<LightObj/>") == 0)
			return (1);
		else if ((pars->balise == 3) && ft_strcmp(line.data, "<HEAD/>") == 0)
			return (1);
		else if ((pars->balise == 4) && ft_strcmp(line.data, "<Camera/>") == 0)
			return (1);
		else if ((pars->balise == 5) && ft_strcmp(line.data, "<NegObj/>") == 0)
			return (1);
		else
			pars_error(pars, "Error : Unknow End Balise", line.data);
	}
	return (0);
}

static int		init_ivar(t_pars *pars, int i)
{
	pars->i_pos = 0;
	pars->i_dir = 0;
	pars->i_radius = 0;
	pars->i_dcp = 0;
	pars->dcp = 0;
	pars->balise = 0;
	return (i);
}

static int		is_var_incr(t_env *env, t_pars *pars)
{
	int		i;

	i = 0;
	if (pars->balise == 1)
	{
		if (pars->i_pos == 1 && pars->i_dir == 1 && pars->i_radius == 1)
			i = 1;
	}
	else if (pars->balise == 2)
	{
		if (pars->i_pos == 1 && pars->i_dir == 1)
			i = 1;
	}
	else if (pars->balise == 4)
	{
		if (pars->i_pos == 1 && pars->i_dir == 1)
			i = 1;
	}
	else if (pars->balise == 5)
	{
		if (pars->i_pos == 1 && pars->i_dir == 1 && pars->i_radius == 1)
			i = 1;
	}
	i = (pars->balise == 3 ? 1 : i);
	return (init_ivar(pars, i));
}

int				is_end_balise(t_env *env, t_pars *pars, t_buff line)
{
	if (end_balise(env, line, pars) == 1)
	{
		if (is_var_incr(env, pars) == 1)
			return (1);
		else
			return (pars_error(pars,
	"Warning : Some Value aren't specified in <balise>", line.data));
	}
	return (0);
}
