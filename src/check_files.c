#include "../rtv1.h"

static void		check_object_name(t_env *env, char *name, t_pars *pars)
{
	if (ft_strcmp(name, "Sphere") == 0)
		init_object(env, pars, SPHERE, env->object);
	else if (ft_strcmp(name, "Plane") == 0)
		init_object(env, pars, PLANE, env->object);
	else if (ft_strcmp(name, "Cylinder") == 0)
		init_object(env, pars, CYLINDER, env->object);
	else if (ft_strcmp(name, "Cone") == 0)
		init_object(env, pars, CONE, env->object);
	else if (ft_strcmp(name, "Spotlight") == 0)
		init_light_obj(env, pars, SPOTLIGHT, env->light);
	else
		ft_error("Error : Wrong object name.\n");
	free(name);
}

static char 	*take_balise_value(char *line, int i)
{
	int		j;
	char	*value;

	j = 0;
	value = (char*)malloc(sizeof(char) * ft_strlen(line));
	if (line[i - 1] == '=')
	{
		while (line[i] != '\0' && line[i] != ';')
		{
			value[j] = line[i];
			i++;
			j++;
		}
		value[j] = '\0';
		if (line[i] != ';')
			ft_error("Syntax Error : Close type value with ';'.\n");
		else
			return (value);
	}
	else
		ft_error("Syntax Error.\n");
	return (value);
}

static char 	*value_of_balise(char *line, char *type)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == type[j] && type[j] != '\0')
			j++;
		if (type[j] == '\0')
		{
			i++;
			value = take_balise_value(line, i);
			return (value);
		}
		i++;
	}
	ft_error("Error : Bad Type Value.\n");
	return (value);
}

static char		*analyse_balise_lign(char *line, char *type)
{
	char	*value;

	if (ft_strstr(line, type) != NULL)
		value = value_of_balise(line, type);
	else
	{
		if (ft_strcmp(type, "name=") == 0)
			ft_error("Error : Bad Type.\n");
		else
			return (NULL);
	}
	return (value);
}

static void		empty_lign(t_buff line)
{
	ft_parse_space(&line);
	if (line.data[line.i] != '\0')
		ft_error("Error : not an empty line between <Object>.\n");
}

static int 		search_param(char *line, char *type)
{
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		while (line[i] != '\0' && line[i] != '\n' && line[i] == type[j])
		{
			i++;
			j++;
			if (type[j] == '\0')
				return (i + 1);
		}
		j = 0;
		i++;
	}
	return (-1);
}

static void		add_double_param(t_buff line, char *type, t_object **object)
{
	t_object	*tmp;

	tmp = *object;
	line.i = search_param(line.data, type);
	if (ft_strcmp(type, "gloss") == 0)
		ft_putnbr(tmp->gloss = ft_parse_double(&line));
	else if (ft_strcmp(type, "transp") == 0)
		tmp->transparency = ft_parse_double(&line);
	else if (ft_strcmp(type, "refraction") == 0)
		tmp->refraction = ft_parse_double(&line);
	else if (ft_strcmp(type, "reflex") == 0)
		tmp->reflex = ft_parse_double(&line);
}

static void		check_object_balise(t_env *env, t_buff line, t_pars *pars)
{
	char	*value;

	if (ft_strstr(line.data, "<Object>") != NULL)
	{
		pars->nbr_lign = 3;
		value = analyse_balise_lign(line.data, "name=");
		check_object_name(env, value, pars);
		value = analyse_balise_lign(line.data, "color=");
		if (value != NULL)
			check_color_obj(env->object, value);
		value = analyse_balise_lign(line.data, "gloss=");
		if (value != NULL)
			add_double_param(line, "gloss", env->object);
		value = analyse_balise_lign(line.data, "transp=");
		if (value != NULL)
			add_double_param(line, "transp", env->object);
		value = analyse_balise_lign(line.data, "reflex=");
		if (value != NULL)
			add_double_param(line, "reflex", env->object);
		value = analyse_balise_lign(line.data, "refraction=");
		if (value != NULL)
			add_double_param(line, "refraction", env->object);
		pars->balise = 1;
	}
	else if (ft_strstr(line.data, "<LightObj>") != NULL)
	{
		pars->nbr_lign = 2;
		value = analyse_balise_lign(line.data, "name=");
		check_object_name(env, value, pars);
		value = analyse_balise_lign(line.data, "color=");
		if (value != NULL)
			check_color_light(env->light, value);
		pars->balise = 2;
	}
	else if (ft_strstr(line.data, "<Camera>") != NULL)
	{
		pars->nbr_lign = 2;
		pars->balise = 3;
	}
	else
		empty_lign(line);
}

static void		pars_object_line(t_env *env, t_buff line, int i)
{
	t_double3	values;

	if (i == 0)
	{
		if (ft_strstr(line.data, "Pos") != NULL)
		{
			check_pars_nbr_value(line, 3);
			values = pick_values(line, 3);
			add_value(env->object, &values, i);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
	if (i == 1)
	{
		if (ft_strstr(line.data, "Rot") != NULL)
		{
			check_pars_nbr_value(line, 3);
			values = pick_values(line, 3);
			add_value(env->object, &values, i);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
	if (i == 2)
	{
		if (ft_strstr(line.data, "Radius") != NULL)
		{
			check_pars_nbr_value(line, 1);
			values = pick_values(line, 1);
			add_value(env->object, &values, i);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
}

static void		pars_light_line(t_env *env, t_buff line, int i)
{
	t_double3	values;

	if (i == 0)
	{
		if (ft_strstr(line.data, "Pos") != NULL)
		{
			check_pars_nbr_value(line, 3);
			values = pick_values(line, 3);
			add_light_value(env->light, &values, i);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
	if (i == 1)
	{
		if (ft_strstr(line.data, "Dir") != NULL)
		{
			check_pars_nbr_value(line, 3);
			values = pick_values(line, 3);
			add_light_value(env->light, &values, i);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
}

static void		pars_camera_line(t_env *env, t_buff line, int i)
{
	t_double3	values;

	if (i == 0)
	{
		if (ft_strstr(line.data, "Pos") != NULL)
		{
			check_pars_nbr_value(line, 3);
			env->camera.pos = pick_values(line, 3);	
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
	if (i == 1)
	{
		if (ft_strstr(line.data, "Dir") != NULL)
		{
			check_pars_nbr_value(line, 3);
			env->camera.dir = pick_values(line, 3);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
}

static int 		end_balise(t_buff line, t_pars *pars)
{
	char 	*str;

	if (pars->balise == 1 && ft_strcmp(line.data, "<Object/>") == 0)
		return (1);
	else if (pars->balise == 2 && ft_strcmp(line.data, "<LightObj/>") == 0)
		return (1);
	else if (pars->balise == 3 && ft_strcmp(line.data, "<Camera/>") == 0)
		return (1);
	return (0);
}

static int		check_object_line_value(t_env *env, t_buff line,
										t_pars *pars, int j)
{
	if (end_balise(line, pars) == 1)
	{
		if (j == pars->nbr_lign)
		{
			pars->balise = 0;
			j = 0;
		}
		else
			ft_error("Error : Wrong Number of Values Lines.\n");
	}
	if (pars->balise == 1)
		pars_object_line(env, line, j++);
	else if (pars->balise == 2)
		pars_light_line(env, line, j++);
	else if (pars->balise == 3)
		pars_camera_line(env, line, j++);
	if (j > pars->nbr_lign)
		ft_error("Error : Too Much of Values Lines, Close the Object.\n");
	return (j);
}

static t_pars	*init_parser()
{
	t_pars	*pars;

	pars = (t_pars*)malloc(sizeof(t_pars*));
	pars->balise = 0;
	pars->nbr_lign = 0;
	pars->i_sphere = -1;
	pars->i_plane = -1;
	pars->i_cylinder = -1;
	pars->i_cone = -1;
	pars->i_light = -1;
	return (pars);
}

void			check_files(int fd, t_env *env)
{
	t_buff		line;
	t_pars		*pars;
	int			j;

	j = 0;
	pars = init_parser();
	env->pars = pars;
	while (get_next_line(fd, &line) > 0)
	{
		ft_putendl(line.data);
		if (pars->balise == 0)
			check_object_balise(env, line, pars);
		else if (pars->balise >= 1)
			j = check_object_line_value(env, line, pars, j);
	}
	if (j < pars->nbr_lign && j != 0)
		ft_error("Error : Wrong Number of Line.\n");
}
