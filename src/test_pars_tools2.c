/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pars_tools2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:54:57 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 16:10:24 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void			empty_lign(t_env *env, t_pars *pars, t_buff line)
{
	ft_parse_space(&line);
	if (line.data[line.i] != '\0')
		pars_error(pars,
			"Error : not an empty line between <Object>.", line.data);
}

char			*check_line_type(t_env *env, t_pars *pars, t_buff line)
{
	int		i;
	char	*type;
	int		error;

	error = 1;
	type = (char*)malloc(sizeof(char) * (ft_strlen(line.data) + 1));
	ft_parse_not(&line, "<");
	i = line.i;
	ft_parse_not(&line, ">");
	if (line.data[line.i] != '>')
		error = pars_error(pars, "Error : close the Balise Signal.", line.data);
	if (line.data[i] != '<')
		error = pars_error(pars, "Error : No Balise Signal.", line.data);
	if (error == 0)
		return (NULL);
	line.i = i + 1;
	i = 0;
	while (line.data[line.i] != '\0' && line.data[line.i] != '>' && i < 10)
	{
		type[i] = line.data[line.i];
		i++;
		line.i++;
	}
	type[i] = '\0';
	return (type);
}

int				is_type_xyz(char *type, int i)
{
	if (type[i] == 'X')
		i = 4;
	else if (type[i] == 'Y')
		i = 5;
	else if (type[i] == 'Z')
		i = 6;
	return (i);
}
