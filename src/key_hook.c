/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 13:36:31 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 22:08:14 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static void		key_updown_menu(t_env *env, int keycode)
{
	if (env->menu->menu_lvl == 0)
	{
		if (keycode == U_ARROW && env->menu->index > 0)
			env->menu->index--;
		else if (keycode == D_ARROW && env->menu->index < 2)
			env->menu->index++;
	}
	else if (env->menu->menu_lvl == 1)
	{
		if (keycode == U_ARROW && env->menu->index > 0)
			env->menu->index--;
	else if (keycode == D_ARROW && env->menu->i_page != env->menu->page_max)
	{
		if (env->menu->index < 4)
				env->menu->index++;
		}
		else if (keycode == D_ARROW && env->menu->i_page == env->menu->page_max)
		{
			if (env->menu->index < env->menu->nbr_scn % 5 - 1)
				env->menu->index++;
		}
	}
}

static void		key_esc_menu(t_env *env)
{
	if (env->menu->menu_lvl == 0)
		exit(0);
	else if (env->menu->menu_lvl == 1 || env->menu->menu_lvl == 2)
		env->menu->menu_lvl = 0;
	env->menu->index = 0;
}

static void		key_leftright_menu(t_env *env, int keycode)
{
	if (env->menu->menu_lvl == 1)
	{
		if (keycode == R_ARROW && env->menu->i_page < env->menu->page_max)
		{
			env->menu->i_page++;
			env->menu->index = 0;
		}
		else if (keycode == L_ARROW && env->menu->i_page > 0)
		{
			env->menu->i_page--;
			env->menu->index = 0;
		}
	}
}

int				key_hook(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		key_esc_menu(env);
	if (keycode == KEY_ENTER)
		key_enter_menu(env);
	if (keycode == U_ARROW || keycode == D_ARROW)
		key_updown_menu(env, keycode);
	if (keycode == L_ARROW || keycode == R_ARROW)
		key_leftright_menu(env, keycode);
	return (0);
}
