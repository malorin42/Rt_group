#include "../rtv1.h"

static void		draw_menu(t_env *env, int x, int y)
{
	if (y <= 50 || x <= 50 || y >= 1150 || x >= 750)
		mlx_pixel_put(env->mlx, env->win_menu, x, y, 0xFFFFFFF);
	if ((x >= 300 && x <= 305) && y >= 100 && y < 150)
		mlx_pixel_put(env->mlx, env->win_menu, x, y, 0xFFFFFFF);
	if ((x >= 495 && x <= 500) && y >= 100 && y < 150)
		mlx_pixel_put(env->mlx, env->win_menu, x, y, 0xFFFFFFF);
	if ((x >= 300 && x <= 500) && y >= 100 && y < 105)
		mlx_pixel_put(env->mlx, env->win_menu, x, y, 0xFFFFFFF);
	if ((x >= 300 && x <= 500) && y >= 150 && y < 155)
		mlx_pixel_put(env->mlx, env->win_menu, x, y, 0xFFFFFFF);
}

void	render_menu(t_env *env)
{
	int 	x;
	int 	y;

	x = 0;
	while(x < 800)
	{
		y = 0;
		while(y < 1200)
		{
			draw_menu(env, x, y);
			y++;
		}
		x++;
	}
}