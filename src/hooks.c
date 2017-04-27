#include "../rtv1.h"

static void		key_enter_menu(t_env *env)
{
	if (env->menu->menu_lvl == 0)
	{
		env->menu->index == 0 ? env->render = 1 : 0;
		if (env->menu->index > 0)
		{
			env->menu->menu_lvl = env->menu->index;
			env->menu->index = 0;
		}
	}
}

static void		key_UpDown_menu(t_env *env, int keycode)
{
	if (env->menu->menu_lvl == 0)
	{
		if (keycode == U_ARROW && env->menu->index > 0)
			env->menu->index--;
		else if (keycode == D_ARROW && env->menu->index < 2)
			env->menu->index++;
	}
}

static void		key_esc_menu(t_env *env)
{
	if (env->menu->menu_lvl == 0)
		exit (0);
	else if (env->menu->menu_lvl == 1 || env->menu->menu_lvl == 2)
		env->menu->menu_lvl = 0;
}

int				key_hook(int keycode, t_env *env)
{
	printf("%i\n", keycode);
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
	// render_menu(env);
	if(env->menu->menu_lvl == 0)
		first_menu(env);
	// if(env->menu->menu_lvl = 1)
		// second_menu(env);
	if(env->menu->menu_lvl == 2)
		third_menu(env);
	if (env->render == 1)
	{
		i = 0;
		multi_threading(env);
		while (i < THREAD)
		{
			mlx_put_image_to_window(env->mlx, env->win_scene, env->img[i]->img, 0, (HEIGHT / THREAD) * i);
			i++;
		}
		
		env->render = 0;
	}
	return (0);
}
