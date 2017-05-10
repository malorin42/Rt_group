#include "../rtv1.h"

static int		end_balise(t_env *env, t_buff line, t_pars *pars)
{
	if (line.data[0] == '<')
	{
		if ((pars->balise == 1) && ft_strcmp(line.data, "<Object/>") == 0)
			return (1);
		else if ((pars->balise == 2) && ft_strcmp(line.data, "<LightObj/>") == 0)
			return (1);
		else if ((pars->balise == 3) && ft_strcmp(line.data, "<HEAD/>") == 0)
			return (1);
		else if ((pars->balise == 4) && ft_strcmp(line.data, "<Camera/>") == 0)
			return (1);
		else if ((pars->balise == 5) && ft_strcmp(line.data, "<NegObj/>") == 0)
			return (1);
		else
			pars_error(pars, "Error : Unknow End Balise", line.data);
	}
	return (0);
}

static void		init_ivar(t_pars *pars)
{
	pars->i_pos = 0;
	pars->i_dir = 0;
	pars->i_radius = 0;
	pars->i_dcp = 0;
	pars->dcp = 0;
	pars->i_dir_light = 0;
	pars->balise = 0;
}

static int 		is_var_incr(t_env *env, t_pars *pars)
{
	int 	i;
	i = 0;
	if (pars->balise == 1)
	{
		if (pars->i_pos == 1 && pars->i_dir == 1 && pars->i_radius == 1)
			i = 1;
	}
	else if (pars->balise == 2)
	{
		if (pars->i_pos == 1 && pars->i_dir == 1)
			i = 1;
	}
	else if (pars->balise == 4)
	{
		if (pars->i_pos == 1 && pars->i_dir == 1)
			i = 1;
	}
	else if (pars->balise == 5)
	{
		if (pars->i_pos == 1 && pars->i_dir == 1 && pars->i_radius == 1)
			i = 1;
	}
	i = (pars->balise == 3 ? 1 : i);
	init_ivar(pars);
	return (i);
}

static int 		is_end_balise(t_env *env, t_pars *pars, t_buff line)
{
	if (end_balise(env, line, pars) == 1)
	{
		if (is_var_incr(env, pars) == 1)
			return (1);
		else
			return (pars_error(pars, "Warning : Some Value aren't specified in <balise>", line.data));
	}
	return (0);
}

static void		check_object_line_value(t_env *env, t_buff line, t_pars *pars)
{
	if (is_end_balise(env, pars, line) == 1)
		return ;
	else if (pars->balise == 3)
		pars_head_balise(env, pars, line);
	else
		pars_in_balise(env, pars, line);
}

static t_pars	*init_parser(void)
{
	t_pars	*pars;

	if ((pars = (t_pars*)malloc(sizeof(t_pars))) == NULL)
		ft_error("Error : Malloc() failed.\n");
	pars->balise = 0;
	pars->ligne = 0;
	pars->i_pos = 0;
	pars->i_dir = 0;
	pars->i_radius = 0;
	pars->i_dcp = 0;
	pars->dcp = 0;
	pars->i_ambiant = 0;
	pars->i_aliai = 0;
	pars->i_dir_light = 0;
	pars->i_sepia = 0;
	pars->i_negative = 0;
	pars->error = 0;
	pars->texture = 0;
	return (pars);
}

void			check_files(int fd, t_env *env)
{
	t_buff		line;
	t_pars		*pars;

	pars = init_parser();
	while (get_next_line(fd, &line) > 0)
	{
		pars->ligne++;
		pars->error = 0;
		pars->actual_line = (char*)malloc(sizeof(char) * ft_strlen(line.data) + 1);
		ft_strcpy(pars->actual_line, line.data);
		if (pars->balise == 0)
			check_if_balise(env, line, pars);
		else
			check_object_line_value(env, line, pars);
	}
	if (pars->actual_line != NULL)
		free(pars->actual_line);
	if (pars != NULL)
		free(pars);
}
