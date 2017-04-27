#include "../rtv1.h"

void	first_menu(t_env *env)
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