#include "../rtv1.h"

static char	*take_balise_value(t_env *env, t_pars *pars, t_buff line, int i)
{
	int		j;
	char	*value;

	j = 0;
	value = (char*)malloc(sizeof(char) * (ft_strlen(line.data) + 1));
	if (line.data[i - 1] == '=')
	{
		while (line.data[i] != '\0' && line.data[i] != ';')
		{
			value[j] = line.data[i];
			i++;
			j++;
		}
		value[j] = '\0';
		if (line.data[i] != ';')
			pars_error(pars, "Syntax Error : Close type value with ';'.", line.data);
		else
			return (value);
	}
	else
		pars_error(pars, "Syntax Error.\n", line.data);
	if (value != NULL)
		free (value);
	return (NULL);
}

static char	*value_of_balise(t_env *env, t_pars *pars, t_buff line, char *type)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (line.data[i] != '\0' && line.data[i] != '\n')
	{
		while (line.data[i] != '\0' && line.data[i] != '\n' &&
			line.data[i] == type[j] && type[j] != '\0')
		{
			j++;
			i++;
		}
		if (type[j] == '\0')
		{
			value = take_balise_value(env, pars, line, i);
			return (value);
		}
		else
			j = 0;
		i++;
	}
	pars_error(pars, "Error : Bad Type Value.", line.data);
	return (NULL);
}

static char	*analyse_balise_lign(t_env *env, t_pars *pars, t_buff line, char *type)
{
	char	*value;

	if (ft_strstr(line.data, type) != NULL)
	{
		if ((value = value_of_balise(env, pars, line, type)) == NULL)
			return (NULL);
		else
			return (value);
	}
	return (NULL);
}

static t_image         *init_texture(void *mlx, char *file)
{
    t_image     *texture;
    int         width;
    int         height;
 
  	ft_putendl(file);
    if ((texture = (t_image*)malloc(sizeof(t_image))) == NULL)
        ft_error("Error: malloc failed.\n");
    texture->img = mlx_xpm_file_to_image(mlx, file, &width, &height);
    texture->data = (unsigned char*)mlx_get_data_addr(texture->img, &texture->opp,
        &texture->l_size, &texture->endian);
    texture->opp = texture->opp / 8;
    texture->width = width;
    texture->height = height;
    return (texture);
}

static int 		lookat_texture_path(char *path, t_pars *pars, t_buff line)
{
	if (open(path, O_RDONLY) < 0)
		return (pars_error(pars, "Error : No xpm.file in ./texture .", line.data));
	pars->texture = 1;
	return (1);
}

static void		add_texture_image(t_env *env, t_object **object, char *path)
{
	t_object	*tmp;

	tmp = *object;
	tmp->texture = init_texture(env->mlx, path);
	if (path != NULL)
		free (path);
}

static void		add_texture(t_env *env, char *value, t_pars *pars, t_buff line)
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

static void		pars_balise_type(t_env *env, t_buff line, t_pars *pars)
{
	char	*value;
	
	value = analyse_balise_lign(env, pars, line, "color=");
	if (value != NULL)
		check_color_obj(line, pars, &env->scene->object, value);
	value = analyse_balise_lign(env, pars, line, "gloss=");
	if (value != NULL)
		add_double_param(line, "gloss", &env->scene->object, value);
	value = analyse_balise_lign(env, pars, line, "transp=");
	if (value != NULL)
		add_double_param(line, "transp", &env->scene->object, value);
	value = analyse_balise_lign(env, pars, line, "reflex=");
	if (value != NULL)
		add_double_param(line, "reflex", &env->scene->object, value);
	value = analyse_balise_lign(env, pars, line, "refraction=");
	if (value != NULL)
		add_double_param(line, "refraction", &env->scene->object, value);
	value = analyse_balise_lign(env, pars, line, "decoupe=");
	if (value != NULL)
		pars->dcp = add_OnOff_value(&env->scene->object, value, pars, line);
	value = analyse_balise_lign(env, pars, line, "texture=");
	if (value != NULL)
		add_texture(env, value, pars, line);
}

static int 		is_balise_type(t_env *env, t_pars *pars, t_buff line)
{
	char	*value;

	value = analyse_balise_lign(env, pars, line, "type=");
	if (value == NULL)
		return (pars_error(pars, "Error : Object Need a Type.", line.data));
	if (check_object_type(env, value, pars, line) == 1)
	{
		pars->balise = 1;
		return (1);
	}
	return (0);
}

static void 	pars_type_light(t_env *env, t_pars *pars, t_buff line)
{
	char	*value;

	init_light_obj(env, pars, &env->scene->light);
	pars->balise = 2;
	value = analyse_balise_lign(env, pars, line, "color=");
	if (value != NULL)
		check_color_light(line, pars, &env->scene->light, value);
}

void			check_if_balise(t_env *env, t_buff line, t_pars *pars)
{
	if (line.data[0] == '<')
	{
		if (ft_strstr(line.data, "<Object>") != NULL)
			is_balise_type(env, pars, line) == 1 ?
			pars_balise_type(env, line, pars) : pars_error(pars, "Error : Unknow Type.", line.data);
		else if (ft_strstr(line.data, "<LightObj>") != NULL)
			pars_type_light(env, pars, line);
		else if (ft_strstr(line.data, "<HEAD>") != NULL)
			pars->balise = 3;
		else if (ft_strstr(line.data, "<Camera>") != NULL)
			pars->balise = 4;
		else if (ft_strstr(line.data, "<NegObj>") != NULL)
		{
			init_neg_obj(env, pars, &env->scene->negobj);
			pars->balise = 5;
		}
		else
			pars_error(pars, "Error : Unknow Balise", line.data);
	}
	else
		empty_lign(env, pars, line);
}
