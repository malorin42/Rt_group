/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahus <jbahus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:51:41 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 16:02:07 by jbahus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static void		draw_main_menu(t_env *env)
{
	mlx_string_put(env->mlx, env->win_menu, 230, 115, 0xF00D532, "MENU");
	if (env->menu->index == 0)
		mlx_string_put(env->mlx, env->win_menu, 130, 250, 0xF00D532, "->");
	mlx_string_put(env->mlx, env->win_menu, 150, 250, 0xF00D532, "Refresh");
	if (env->menu->index == 1)
		mlx_string_put(env->mlx, env->win_menu, 130, 300, 0xF00D532, "->");
	mlx_string_put(env->mlx, env->win_menu,
		150, 300, 0xF00D532, "Liste des scenes");
	if (env->menu->index == 2)
		mlx_string_put(env->mlx, env->win_menu, 130, 350, 0xF00D532, "->");
	mlx_string_put(env->mlx, env->win_menu,
		150, 350, 0xF00D532, "Enregistrer L'image");
}

void			draw_menu(t_env *env)
{
	if (env->menu->menu_lvl == 0)
		draw_main_menu(env);
	else if (env->menu->menu_lvl == 1)
		setup_scene_menu(env);
}
