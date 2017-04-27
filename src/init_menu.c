#include "../rtv1.h"

void			init_menu(t_env *env)
{
	env->win_menu = mlx_new_window(env->mlx, 800, 1200, "Menu");
	mlx_key_hook(env->win_menu, &key_hook, env);
	env->menu = (t_menu*)malloc(sizeof(t_menu));
	env->menu->index = 0;
	env->menu->render = 0;
	env->menu->menu_lvl = 0;
}