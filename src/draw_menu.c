#include "../rtv1.h"

static int		add_scene_to_tab(char **tab, char *scn, int i)
{
	if (i < 0)
	{
		i = -i;
		tab[i] = (char*)malloc(sizeof(char) * 5);
		strcpy(tab[i], "FIN\0");
		return (1);
	}
	tab[i] = (char*)malloc(sizeof(char) * ft_strlen(scn) + 1);
	if (wrong_files(scn) == 1)
	{
		strcpy(tab[i], scn);
		return (1);
	}
	else
		return (0);
}

static void		write_page_status(t_env *env)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * 18);
	str = ft_strjoin(str, "Page : ");
	str = ft_strjoin(str, ft_itoa(env->menu->i_page));
	str = ft_strjoin(str, " / ");
	str = ft_strjoin(str, ft_itoa(env->menu->page_max));
	mlx_string_put(env->mlx, env->win_menu, 50, 200, 0xF00D532, str);
}

static void		draw_scene_menu(t_env *env, char **tab)
{
	int		i;
	int		imax;
	int		y;

	y = 250;
	i = env->menu->i_page * 5;
	imax = i + 5;
	write_page_status(env);
	while (i < imax)
	{
		if (ft_strcmp(tab[i], "FIN") == 0)
			return ;
		mlx_string_put(env->mlx, env->win_menu, 150, y, 0xF00D532, tab[i]);
		y += 50;
		i++;
	}
}

// static void		free_tab_scn(char **tab)
// {
// 	int		i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }

static void		setup_scene_menu(t_env *env)
{
	DIR				*flux;
	struct dirent	*dir;
	int 			y;
	int				i;

	y = 300;
	i = 0;
	flux = opendir("./scenes");
	env->menu->tab_scn = (char**)malloc(sizeof(char*) * 50);
	mlx_string_put(env->mlx, env->win_menu, 175, 115, 0xF00D532, "Liste des scenes");
	while ((dir = readdir(flux)))
	{
		if (ft_strcmp(dir->d_name, "..") != 0 && ft_strcmp(dir->d_name, ".") != 0)
		{
			if (add_scene_to_tab(env->menu->tab_scn, dir->d_name, i) == 1)
				i++;
		}
	}
	add_scene_to_tab(env->menu->tab_scn, "", -i);
	closedir(flux);
	env->menu->nbr_scn = i;
	env->menu->page_max = i % 5;
	draw_scene_menu(env, env->menu->tab_scn);
	i = env->menu->index;
	mlx_string_put(env->mlx, env->win_menu, 130, 250 + (50 * i), 0xF00D532, "->");
	// free_tab_scn(env->menu->tab_scn);
}

static void		draw_main_menu(t_env *env)
{
	mlx_string_put(env->mlx, env->win_menu, 230, 115, 0xF00D532, "MENU");
	if (env->menu->index == 0)
		mlx_string_put(env->mlx, env->win_menu, 130, 250, 0xF00D532, "->");
	mlx_string_put(env->mlx, env->win_menu, 150, 250, 0xF00D532, "Refresh");
	if (env->menu->index == 1)
		mlx_string_put(env->mlx, env->win_menu, 130, 300, 0xF00D532, "->");
	mlx_string_put(env->mlx, env->win_menu, 150, 300, 0xF00D532, "Liste des scenes");
	if (env->menu->index == 2)
		mlx_string_put(env->mlx, env->win_menu, 130, 350, 0xF00D532, "->");
	mlx_string_put(env->mlx, env->win_menu, 150, 350, 0xF00D532, "Enregistrer L'image");
}

void			draw_menu(t_env *env)
{
	if (env->menu->menu_lvl == 0)
		draw_main_menu(env);
	else if (env->menu->menu_lvl == 1)
		setup_scene_menu(env);
}