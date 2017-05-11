/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_balise_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:34:10 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 20:06:49 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static char	*take_balise_value(t_env *env, t_pars *pars, t_buff line, int i)
{
	int		j;
	char	*value;

	j = 0;
	value = (char*)malloc(sizeof(char) * (ft_strlen(line.data) + 1));
	if (line.data[i - 1] == '=')
	{
		while (line.data[i] != '\0' && line.data[i] != ';')
		{
			value[j] = line.data[i];
			i++;
			j++;
		}
		value[j] = '\0';
		if (line.data[i] != ';')
			pars_error(pars, "Syntax Error : Close type value with ';'.",
				line.data);
		else
			return (value);
	}
	else
		pars_error(pars, "Syntax Error.\n", line.data);
	if (value != NULL)
		free(value);
	return (NULL);
}

static char	*value_of_balise(t_env *env, t_pars *pars, t_buff line, char *type)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (line.data[i] != '\0' && line.data[i] != '\n')
	{
		while (line.data[i] != '\0' && line.data[i] != '\n' &&
			line.data[i] == type[j] && type[j] != '\0')
		{
			j++;
			i++;
		}
		if (type[j] == '\0')
		{
			value = take_balise_value(env, pars, line, i);
			return (value);
		}
		else
			j = 0;
		i++;
	}
	pars_error(pars, "Error : Bad Type Value.", line.data);
	return (NULL);
}

char		*analyse_balise_lign(t_env *env, t_pars *pars, t_buff line,
	char *type)
{
	char	*value;

	if (ft_strstr(line.data, type) != NULL)
	{
		if ((value = value_of_balise(env, pars, line, type)) == NULL)
			return (NULL);
		else
			return (value);
	}
	return (NULL);
}

void		add_perturbation(t_object **object, char *value, t_pars *pars,
	t_buff line)
{
	t_object	*tmp;

	tmp = *object;
	if (ft_strcmp(value, "damier") == 0)
		tmp->perturbation = 1;
	else if (ft_strcmp(value, "perlin") == 0)
		tmp->perturbation = 2;
	else
		pars_error(pars, "Error : Unknow Perturbation name.", line.data);
}
