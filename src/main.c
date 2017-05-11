/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 17:08:04 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 20:06:25 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

int				red_cross(t_env env)
{
	exit(0);
	return (0);
}

void			init_scene(t_env *env)
{
	env->scene->object = NULL;
	env->scene->light = NULL;
	env->scene->negobj = NULL;
	env->scene->ambiant = 0.2;
	env->scene->aliaising = 0;
	env->scene->cell_shading = 0;
	env->scene->direct_light = 0;
	env->scene->sepia = 0;
	env->scene->neg = 0;
}

static t_env	*env_init(void)
{
	t_env		*env;
	int			i;

	i = 0;
	if ((env = (t_env*)malloc(sizeof(t_env))) == NULL)
		ft_error("Error : malloc() failed.\n");
	if ((env->mlx = mlx_init()) == NULL)
		ft_error("Error : mlx_init() failed.\n");
	env->win_scene = mlx_new_window(env->mlx, WIDTH, HEIGHT, "RTv1");
	while (i < THREAD)
		env->img[i++] = ft_new_image(env->mlx, WIDTH, HEIGHT, THREAD);
	env->nbr_obj = 0;
	env->scene = (t_scene*)malloc(sizeof(t_scene));
	env->win_menu = mlx_new_window(env->mlx, 500, 600, "Menu");
	env->scene->camera = (t_vector){(t_double3){0, 0, 0}, (t_double3){0, 0, 0}};
	init_scene(env);
	pthread_mutex_init(&env->my_mutex, NULL);
	pthread_cond_init(&env->cond, NULL);
	mlx_key_hook(env->win_scene, &key_hook, env);
	mlx_hook(env->win_scene, DESTROYNOTIFY, STRUCTURENOTIFYMASK,
		red_cross, &env);
	mlx_hook(env->win_menu, DESTROYNOTIFY, STRUCTURENOTIFYMASK,
		red_cross, &env);
	mlx_loop_hook(env->mlx, &loop_hook, env);
	return (env);
}

int				wrong_files(char const *str)
{
	int			i;
	int			j;
	char		*scn;

	i = 0;
	scn = ".scn";
	while (str[i] != '\0' && str[i] != '.')
		i++;
	if (str[i] == '.')
	{
		j = 0;
		while (str[i] != '\0' && j <= 3)
		{
			if (str[i] != scn[j])
				return (0);
			i++;
			j++;
		}
	}
	else
		return (0);
	return (1);
}

int				main(int argc, char const **argv)
{
	t_env		*env;
	int			fd;

	if (argc != 2)
		ft_error("Error : Wrong numbers of Arguments.\n");
	if (wrong_files(argv[1]) != 1)
		ft_error("Error : File isn't a '.scn'\n");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("Error : File not found.\n");
	env = env_init();
	init_menu(env, argv[1]);
	check_files(fd, env);
	mlx_string_put(((t_env*)env)->mlx, ((t_env*)env)->win_scene,
		100, 100, 0xF00D532, "Loading...");
	close(fd);
	mlx_loop(env->mlx);
	return (0);
}
