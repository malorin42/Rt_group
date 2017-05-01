#include "../rtv1.h"

static void		draw_scene_menu(t_env *env)
{
	DIR				*flux;
	struct dirent	*dir;
	int 			y;
	int				i;

	y = 300;
	i = 0;
	flux = opendir("./scenes");
	mlx_string_put(env->mlx, env->win_menu, 325, 115, 0xF00D532, "Liste des scenes");
	while((dir = readdir(flux)))
	{
		if (ft_strcmp(dir->d_name, "..") != 0 && ft_strcmp(dir->d_name, ".") != 0)
		{
			mlx_string_put(env->mlx, env->win_menu, 150, y, 0xF00D532, dir->d_name);
			y += 50;
			i++;
		}
	}
	closedir(flux);
	if (env->menu->index == i)
		env->menu->index = 0;
	if (env->menu->index < 0)
		env->menu->index = i - 1;
	mlx_string_put(env->mlx, env->win_menu, 130, 300 + (50 * env->menu->index), 0xF00D532, "->");
}

static void		draw_main_menu(t_env *env)
{
	mlx_string_put(env->mlx, env->win_menu, 380, 115, 0xF00D532, "MENU");
	if (env->menu->index == 0)
		mlx_string_put(env->mlx, env->win_menu, 130, 300, 0xF00D532, "->");
	mlx_string_put(env->mlx, env->win_menu, 150, 300, 0xF00D532, "Refresh");
	if (env->menu->index == 1)
		mlx_string_put(env->mlx, env->win_menu, 130, 350, 0xF00D532, "->");
	mlx_string_put(env->mlx, env->win_menu, 150, 350, 0xF00D532, "Liste des scenes");
}

void			draw_menu(t_env *env)
{
	if (env->menu->menu_lvl == 0)
		draw_main_menu(env);
	else if (env->menu->menu_lvl == 1)
		draw_scene_menu(env);
}