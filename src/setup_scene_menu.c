/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_scene_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahus <jbahus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:00:44 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 21:45:53 by jbahus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static int		add_scene_to_tab(char **tab, char *scn, int i)
{
	if (i < 0)
	{
		i = -i;
		tab[i] = NULL;
		return (1);
	}
	if (i < 49)
		tab[i] = (char*)malloc(sizeof(char) * ft_strlen(scn) + 1);
	else
		return (0);
	if (wrong_files(scn) == 1)
	{
		tab[i] = ft_strcpy(tab[i], scn);
		return (1);
	}
	else
		return (0);
}

static void		write_page_status(t_env *env)
{
	char	*str;
	char	*tmp;
	char	*tmp2;

	str = ft_strjoin(str, "Page : ");
	tmp = ft_itoa(env->menu->i_page);
	tmp2 = ft_strjoin(str, tmp);
	free(tmp);
	free(str);
	tmp = ft_strjoin(tmp2, " / ");
	free(tmp2);
	tmp2 = ft_itoa(env->menu->page_max);
	str = ft_strjoin(tmp, tmp2);
	free(tmp);
	free(tmp2);
	mlx_string_put(env->mlx, env->win_menu, 50, 200, 0xF00D532, str);
	free(str);
	if (env->menu->i_page == 0)
		ft_draw_left_arrow(env);
	if (env->menu->i_page == env->menu->page_max)
		ft_draw_right_arrow(env);
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
		if (!tab[i])
			return ;
		mlx_string_put(env->mlx, env->win_menu, 150, y, 0xF00D532, tab[i]);
		y += 50;
		i++;
	}
}

static void		d_name_cmp(t_env *env, char *d_name, int *i)
{
	if (ft_strcmp(d_name, "..") != 0 && ft_strcmp(d_name, ".")
		!= 0 && ft_strcmp(d_name, "saved") != 0)
	{
		if (add_scene_to_tab(env->menu->tab_scn, d_name, *i) == 1)
			*i += 1;
	}
}

void			setup_scene_menu(t_env *env)
{
	DIR				*flux;
	struct dirent	*dir;
	int				y;
	int				i;

	y = 300;
	i = 0;
	flux = opendir("./scenes");
	env->menu->tab_scn = (char**)malloc(sizeof(char*) * 50);
	mlx_string_put(env->mlx, env->win_menu, 175, 115,
		0xF00D532, "Liste des scenes");
	while ((dir = readdir(flux)))
		d_name_cmp(env, dir->d_name, &i);
	add_scene_to_tab(env->menu->tab_scn, "", -i);
	closedir(flux);
	env->menu->nbr_scn = i;
	env->menu->page_max = i / 5;
	draw_scene_menu(env, env->menu->tab_scn);
	i = env->menu->index;
	mlx_string_put(env->mlx, env->win_menu, 130,
		250 + (50 * i), 0xF00D532, "->");
}
