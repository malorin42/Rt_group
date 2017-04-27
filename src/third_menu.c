#include "../rtv1.h"

void	third_menu(t_env *env)
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