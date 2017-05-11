/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:02:50 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 16:58:44 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

void			init_menu(t_env *env, const char *argv)
{
	mlx_key_hook(env->win_menu, &key_hook, env);
	env->menu = (t_menu*)malloc(sizeof(t_menu));
	env->menu->index = 0;
	env->menu->render = 1;
	env->menu->menu_lvl = 0;
	env->menu->i_page = 0;
	env->menu->page_max = 0;
	env->menu->nbr_scn = 0;
	env->menu->path = (char*)malloc(sizeof(char) * strlen("./scenes/")
		+ strlen(argv));
	env->menu->path = ft_strcpy(env->menu->path, argv);
	env->menu->img = ft_new_image(env->mlx, 800, 1200, 1);
	render_menu(env);
}
