/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_enter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahus <jbahus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 13:38:28 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 14:03:42 by jbahus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static void		refresh(t_env *env)
{
	int		fd;
	int		i;

	i = 0;
	if ((fd = open(env->menu->path, O_RDONLY)) < 0)
		ft_error("Error : File not found.\n");
	env->scene->object = NULL;
	env->scene->light = NULL;
	check_files(fd, env);
	while (i < THREAD)
	{
		ft_bzero(env->img[i]->data, env->img[i]->l_size);
		i++;
	}
	env->menu->render = 1;
	mlx_string_put(((t_env*)env)->mlx, ((t_env*)env)->win_scene,
		100, 100, 0xF00D532, "Loading...");
}

static void		change_scene(t_env *env)
{
	int			i;

	i = 0;
	while (env->menu->tab_scn[i] != NULL)
	{
		if (i == env->menu->index + (env->menu->i_page * 5))
		{
			env->menu->path = (char*)malloc(sizeof(char) * (strlen("scenes/")
				+ strlen(env->menu->tab_scn[i])));
			env->menu->path = ft_strcat(ft_strcat(env->menu->path, "scenes/"),
				env->menu->tab_scn[i]);
		}
		i++;
	}
}

void			key_enter_menu(t_env *env)
{
	if (env->menu->menu_lvl == 0)
	{
		env->menu->index == 0 ? refresh(env) : 0;
		env->menu->index == 2 ? save_img(env) : 0;
		if (env->menu->index == 1)
		{
			env->menu->menu_lvl = 1;
			env->menu->index = 0;
			env->menu->i_page = 0;
		}
		else if (env->menu->index == 2)
			save_img(env);
	}
	else if (env->menu->menu_lvl == 1)
	{
		change_scene(env);
		env->menu->menu_lvl = 0;
		env->menu->index = 0;
	}
}