/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_enter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 13:38:28 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 20:06:16 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void	free_obj(t_object *obj)
{
	if (obj->next)
		free_obj(obj->next);
	free(obj->texture);
	free(obj);
}

void	free_light(t_light *light)
{
	if (light->next)
		free_light(light->next);
	free(light->texture);
	free(light);
}

void	init_scene_2(t_env *env)
{
	if (env->scene->object)
		free_obj(env->scene->object);
	if (env->scene->light)
		free_light(env->scene->light);
	if (env->scene->negobj)
		free(env->scene->negobj);
	init_scene(env);
}

static void		refresh(t_env *env)
{
	int		fd;
	int		i;

	i = 0;
	if ((fd = open(env->menu->path, O_RDONLY)) < 0)
		ft_error("Error : File not found.\n");
	init_scene_2(env);
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
