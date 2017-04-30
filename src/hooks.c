#include "../rtv1.h"

static void		refresh(t_env *env)
{
	int		fd;
	int		i;

	i = 0;
	ft_putendl(env->menu->path);
	if ((fd = open(env->menu->path, O_RDONLY)) < 0)
		ft_error("Error : File not found.\n");
	env->scene->object = NULL;
	env->scene->light = NULL;
	check_files(fd, env);
	while(i < THREAD)
	{
		ft_bzero(env->img[i]->data, env->img[i]->l_size);
		i++;
	}
	env->menu->render = 1;
}

static void		change_scene(t_env *env)
{
	DIR				*flux;
	struct dirent	*dir;
	int 			i;

	i = 0;
	flux = opendir("./scenes");
	while((dir = readdir(flux)))
	{
		if (ft_strcmp(dir->d_name, "..") != 0 && ft_strcmp(dir->d_name, ".") != 0)
			i++;
		if (i == env->menu->index + 1)
		{
			env->menu->path = (char*)malloc(sizeof(char) * strlen("./scenes/") + strlen(dir->d_name));
			env->menu->path = ft_strcat(ft_strcat(env->menu->path, "./scenes/"), dir->d_name);
		}
	}
	closedir(flux);
}

static void		key_enter_menu(t_env *env)
{
	if (env->menu->menu_lvl == 0)
	{
		env->menu->index == 0 ? refresh(env) : 0;
		if (env->menu->index > 0)
		{
			env->menu->menu_lvl = env->menu->index;
			env->menu->index = 0;
		}
	}
	else if (env->menu->menu_lvl == 1)
	{
		change_scene(env);
		env->menu->menu_lvl = 0;
		env->menu->index = 0;
	}
}

static void		key_UpDown_menu(t_env *env, int keycode)
{
	if (env->menu->menu_lvl == 0)
	{
		if (keycode == U_ARROW && env->menu->index > 0)
			env->menu->index--;
		else if (keycode == D_ARROW && env->menu->index < 1)
			env->menu->index++;
	}
	else if (env->menu->menu_lvl == 1)
	{
		if (keycode == U_ARROW)
			env->menu->index--;
		else if (keycode == D_ARROW)
			env->menu->index++;
	}
}

static void		key_esc_menu(t_env *env)
{
	if (env->menu->menu_lvl == 0)
		exit (0);
	else if (env->menu->menu_lvl == 1 || env->menu->menu_lvl == 2)
		env->menu->menu_lvl = 0;
	env->menu->index = 0;
}

int				key_hook(int keycode, t_env *env)
{
	// printf("%i\n", keycode);
	if (keycode == KEY_ESC)
		key_esc_menu(env);
	if (keycode == KEY_ENTER)
		key_enter_menu(env);
	if (keycode == U_ARROW || keycode == D_ARROW)
		key_UpDown_menu(env, keycode);
	return (0);
}

int				loop_hook(t_env *env)
{
	int 		i;

	mlx_clear_window(env->mlx, env->win_menu);
	mlx_put_image_to_window(env->mlx, env->win_menu, env->menu->img->img, 0, 0);
	draw_menu(env);
	if (env->menu->render == 1)
	{
		i = 0;
		multi_threading(env);
		while (i < THREAD)
		{
			mlx_put_image_to_window(env->mlx, env->win_scene, env->img[i]->img, 0, (HEIGHT / THREAD) * i);
			i++;
		}
		env->menu->render = 0;
	}
	return (0);
}
