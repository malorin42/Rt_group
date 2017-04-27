#include "../rtv1.h"

static void		draw_scene_menu(t_env *env)
{
	DIR				*flux;
	struct dirent	*dir;
	int 			y;

	y = 300;
	flux = opendir("./scenes");
	mlx_string_put(env->mlx, env->win_menu, 352, 130, 0xF00D532, "Liste des scenes");
	while((dir = readdir(flux)))
	{
		if (ft_strcmp(dir->d_name, "..") != 0 && ft_strcmp(dir->d_name, ".") != 0)
		{
			mlx_string_put(env->mlx, env->win_menu, 150, y, 0xF00D532, dir->d_name);
			y += 50;
		}
	}
	closedir(flux);
}

static void		draw_main_menu(t_env *env)
{
	mlx_string_put(env->mlx, env->win_menu, 395, 130, 0xF00D532, "MENU");
	if (env->menu->index == 0)
		mlx_string_put(env->mlx, env->win_menu, 130, 300, 0xF00D532, "->");
	mlx_string_put(env->mlx, env->win_menu, 150, 300, 0xF00D532, "Refresh");
	if (env->menu->index == 1)
		mlx_string_put(env->mlx, env->win_menu, 130, 350, 0xF00D532, "->");
	mlx_string_put(env->mlx, env->win_menu, 150, 350, 0xF00D532, "Liste des objets");
	if (env->menu->index == 2)
		mlx_string_put(env->mlx, env->win_menu, 130, 400, 0xF00D532, "->");
	mlx_string_put(env->mlx, env->win_menu, 150, 400, 0xF00D532, "Liste des scenes");
}

void			draw_menu(t_env *env)
{
	// render_menu(env);
	if (env->menu->menu_lvl == 0)
		draw_main_menu(env);
	// else if (env->menu->menu_lvl == 1)
	// 	draw_???_menu(env);
	else if (env->menu->menu_lvl == 2)
		draw_scene_menu(env);
}