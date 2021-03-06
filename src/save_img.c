/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:02:50 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 20:07:41 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../rt.h"

static void		create_header(t_header *header, t_info *h_infos, t_image *img)
{
	header->type[0] = 0x42;
	header->type[1] = 0x4D;
	header->file_size = 54 + (img->l_size * img->height);
	header->reserved = 0x00000000;
	header->offset = 54;
	h_infos->header_size = 40;
	h_infos->height = HEIGHT;
	h_infos->width = WIDTH;
	h_infos->panes = 1;
	h_infos->bpp = 24;
	h_infos->compression = 0;
	h_infos->img_size = img->l_size * img->height;
	h_infos->x_res = 2835;
	h_infos->y_res = 2835;
	h_infos->nb_color = 0;
	h_infos->important_color = 0;
}

static void		write_header(const int fd, t_header header, t_info h_infos)
{
	write(fd, &header.type, 2);
	write(fd, &header.file_size, 4);
	write(fd, &header.reserved, 4);
	write(fd, &header.offset, 4);
	write(fd, &h_infos.header_size, 4);
	write(fd, &h_infos.width, 4);
	write(fd, &h_infos.height, 4);
	write(fd, &h_infos.panes, 2);
	write(fd, &h_infos.bpp, 2);
	write(fd, &h_infos.compression, 4);
	write(fd, &h_infos.img_size, 4);
	write(fd, &h_infos.x_res, 4);
	write(fd, &h_infos.y_res, 4);
	write(fd, &h_infos.nb_color, 4);
	write(fd, &h_infos.important_color, 4);
}

static char		*cpy_img(char *copy, t_image img, int i, int *j)
{
	int		k;

	k = 0;
	while (k < img.l_size)
	{
		copy[*j] = img.data[i + k + 1];
		copy[*j + 1] = img.data[i + k + 2];
		copy[*j + 2] = img.data[i + k + 3];
		*j += 3;
		k += 4;
	}
	return (copy);
}

static char		*create_img(t_env *env)
{
	int		i;
	int		j;
	int		t;
	char	*copy;

	j = 0;
	t = THREAD - 1;
	if (!(copy = (char*)malloc(sizeof(char) * env->h_infos.img_size)))
		ft_error("malloc error in creation of saved image.");
	while (t >= 0)
	{
		i = (env->h_infos.img_size / THREAD) - 1;
		while (i >= 0)
		{
			i -= env->img[t]->l_size;
			copy = cpy_img(copy, *env->img[t], i, &j);
		}
		t--;
	}
	return (copy);
}

void			save_img(t_env *env)
{
	int			fd;
	t_image		*tmp;
	char		*pixel_data;
	char		*path;

	path = ft_strjoin("saved/", env->menu->path + 7);
	path = ft_strjoin(path, ".bmp");
	if ((fd = open(path, O_WRONLY | O_CREAT, OPEN_FLAG)) == -1)
		ft_error("Something went wrong with creation of image.");
	tmp = ft_new_image(env->mlx, WIDTH, HEIGHT, 1);
	create_header(&env->header, &env->h_infos, tmp);
	write_header(fd, env->header, env->h_infos);
	pixel_data = create_img(env);
	write(fd, pixel_data, env->h_infos.img_size);
	close(fd);
	free(path);
}
