#include "../rtv1.h"

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
}