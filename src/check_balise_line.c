/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_balise_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 21:25:17 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 18:23:29 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static void		pars_balise_type2(t_env *env, t_buff line, t_pars *pars)
{
	char	*value;

	value = analyse_balise_lign(env, pars, line, "decoupe=");
	if (value != NULL)
		pars->dcp = add_on_off_value(&env->scene->object, value, pars, line);
	value = analyse_balise_lign(env, pars, line, "texture=");
	if (value != NULL)
		add_texture(env, value, pars, line);
	value = analyse_balise_lign(env, pars, line, "Perturb=");
	if (value != NULL)
		add_perturbation(&env->scene->object, value, pars, line);
}

static void		pars_balise_type(t_env *env, t_buff line, t_pars *pars)
{
	char	*value;

	value = analyse_balise_lign(env, pars, line, "color=");
	if (value != NULL)
		check_color_obj(line, pars, &env->scene->object, value);
	value = analyse_balise_lign(env, pars, line, "gloss=");
	if (value != NULL)
		add_double_param(line, "gloss", &env->scene->object, value);
	value = analyse_balise_lign(env, pars, line, "transp=");
	if (value != NULL)
		add_double_param(line, "transp", &env->scene->object, value);
	value = analyse_balise_lign(env, pars, line, "reflex=");
	if (value != NULL)
		add_double_param(line, "reflex", &env->scene->object, value);
	value = analyse_balise_lign(env, pars, line, "refraction=");
	if (value != NULL)
		add_double_param(line, "refraction", &env->scene->object, value);
	pars_balise_type2(env, line, pars);
}

static int		is_balise_type(t_env *env, t_pars *pars, t_buff line)
{
	char	*value;

	value = analyse_balise_lign(env, pars, line, "type=");
	if (value == NULL)
		return (pars_error(pars, "Error : Object Need a Type.", line.data));
	if (check_object_type(env, value, pars, line) == 1)
	{
		pars->balise = 1;
		return (1);
	}
	return (0);
}

static void		pars_type_light(t_env *env, t_pars *pars, t_buff line)
{
	char	*value;

	init_light_obj(env, pars, &env->scene->light, line);
	pars->balise = 2;
	value = analyse_balise_lign(env, pars, line, "color=");
	if (value != NULL)
		check_color_light(line, pars, &env->scene->light, value);
}

void			check_if_balise(t_env *env, t_buff line, t_pars *pars)
{
	if (line.data[0] == '<')
	{
		if (ft_strstr(line.data, "<Object>") != NULL)
			is_balise_type(env, pars, line) == 1 ?
			pars_balise_type(env, line, pars) : pars_error(pars,
			"Error : Unknow Type.", line.data);
		else if (ft_strstr(line.data, "<LightObj>") != NULL)
			pars_type_light(env, pars, line);
		else if (ft_strstr(line.data, "<HEAD>") != NULL)
			pars->balise = 3;
		else if (ft_strstr(line.data, "<Camera>") != NULL)
			pars->balise = 4;
		else if (ft_strstr(line.data, "<NegObj>") != NULL)
		{
			init_neg_obj(env, pars, &env->scene->negobj);
			pars->balise = 5;
		}
		else
			pars_error(pars, "Error : Unknow Balise", line.data);
	}
	else
		empty_lign(env, pars, line);
}
