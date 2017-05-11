/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 15:28:58 by malorin           #+#    #+#             */
/*   Updated: 2017/05/11 15:33:57 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rtv1.h"

static t_image		*init_texture(void *mlx, char *file)
{
	t_image		*texture;
	int			width;
	int			height;

	if ((texture = (t_image*)malloc(sizeof(t_image))) == NULL)
		ft_error("Error: malloc failed.\n");
	texture->img = mlx_xpm_file_to_image(mlx, file, &width, &height);
	texture->data = (unsigned char*)mlx_get_data_addr(texture->img,
		&texture->opp, &texture->l_size, &texture->endian);
	texture->opp = texture->opp / 8;
	texture->width = width;
	texture->height = height;
	return (texture);
}

static int			lookat_texture_path(char *path, t_pars *pars, t_buff line)
{
	if (open(path, O_RDONLY) < 0)
		return (pars_error(pars, "Error : No xpm.file .", line.data));
	pars->texture = 1;
	return (1);
}

static void			add_texture_image(t_env *env, t_object **object, char *path)
{
	t_object	*tmp;

	tmp = *object;
	tmp->texture = init_texture(env->mlx, path);
	if (path != NULL)
		free(path);
}

void				add_texture(t_env *env, char *value, t_pars *pars,
	t_buff line)
{
	char	*path;

	path = (char*)malloc(sizeof(char) * ft_strlen(value) + 16);
	ft_strcpy(path, "./texture/");
	path = ft_strjoin(path, value);
	path = ft_strjoin(path, ".xpm");
	if (lookat_texture_path(path, pars, line) == 0)
		return ;
	add_texture_image(env, &env->scene->object, path);
}
