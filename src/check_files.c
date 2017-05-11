/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 20:32:46 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 20:04:47 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static void		check_object_line_value(t_env *env, t_buff line, t_pars *pars)
{
	if (is_end_balise(env, pars, line) == 1)
		return ;
	else if (pars->balise == 3)
		pars_head_balise(env, pars, line);
	else
		pars_in_balise(env, pars, line);
}

static t_pars	*init_parser(void)
{
	t_pars	*pars;

	if ((pars = (t_pars*)malloc(sizeof(t_pars))) == NULL)
		ft_error("Error : Malloc() failed.\n");
	pars->balise = 0;
	pars->ligne = 0;
	pars->i_pos = 0;
	pars->i_dir = 0;
	pars->i_radius = 0;
	pars->i_dcp = 0;
	pars->dcp = 0;
	pars->i_ambiant = 0;
	pars->i_aliai = 0;
	pars->i_dir_light = 0;
	pars->i_sepia = 0;
	pars->i_negative = 0;
	pars->error = 0;
	pars->texture = 0;
	return (pars);
}

void			check_files(int fd, t_env *env)
{
	t_buff		line;
	t_pars		*pars;

	pars = init_parser();
	while (get_next_line(fd, &line) > 0)
	{
		pars->ligne++;
		pars->error = 0;
		pars->actual_line = (char*)malloc(sizeof(char) *
			ft_strlen(line.data) + 1);
		ft_strcpy(pars->actual_line, line.data);
		if (pars->balise == 0)
			check_if_balise(env, line, pars);
		else
			check_object_line_value(env, line, pars);
	}
	if (pars->actual_line != NULL)
		free(pars->actual_line);
	if (pars != NULL)
		free(pars);
}
