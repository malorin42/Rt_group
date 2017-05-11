/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 13:40:08 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 20:05:56 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static void			*wait_draw(void *env)
{
	mlx_string_put(((t_env*)env)->mlx, ((t_env*)env)->win_scene,
		100, 100, 0xF00D532, ((t_env*)env)->win_scene);
	pthread_exit(0);
}

int					loop_hook(t_env *env)
{
	int			i;
	pthread_t	th;

	if (env->menu->render == 1)
	{
		mlx_clear_window(env->mlx, env->win_scene);
		if (pthread_create(&th, NULL, wait_draw, env) != 0)
			ft_error("Thread create went wrong.");
		i = 0;
		multi_threading(env);
		pthread_join(th, NULL);
		while (i < THREAD)
		{
			mlx_put_image_to_window(env->mlx, env->win_scene, env->img[i]->img,
				0, (HEIGHT / THREAD) * i);
			i++;
		}
		env->menu->render = 0;
	}
	mlx_clear_window(env->mlx, env->win_menu);
	mlx_put_image_to_window(env->mlx, env->win_menu, env->menu->img->img, 0, 0);
	draw_menu(env);
	return (0);
}
