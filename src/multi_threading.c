/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 12:56:17 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 20:06:37 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

void			multi_threading(t_env *env)
{
	pthread_t	th[THREAD];

	env->count = 0;
	if (HEIGHT % THREAD != 0)
		ft_error("Wrong thread number.");
	while (env->count < THREAD)
	{
		if (pthread_create(&th[env->count], NULL, render, env) != 0)
			ft_error("Thread create went wrong.");
		pthread_mutex_lock(&env->my_mutex);
		pthread_cond_wait(&env->cond, &env->my_mutex);
		env->count++;
		pthread_mutex_unlock(&env->my_mutex);
	}
	pthread_mutex_lock(&env->my_mutex);
	env->count = 0;
	pthread_mutex_unlock(&env->my_mutex);
	while (env->count < THREAD)
	{
		pthread_join(th[env->count], NULL);
		env->count++;
	}
}
