#include "../rtv1.h"

static void	pars_object_line3(t_env *env, t_buff line, int i)
{
	t_double3	values;

	if (i == 4)
	{
		if (ft_strstr(line.data, "Min") != NULL)
		{
			check_pars_nbr_value(line, 3);
			values = pick_values(line, 3);
			add_value(env, &values, i);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
	if (i == 5)
	{
		if (ft_strstr(line.data, "Max") != NULL)
		{
			check_pars_nbr_value(line, 3);
			values = pick_values(line, 3);
			add_value(env, &values, i);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
}

static void	pars_object_line2(t_env *env, t_buff line, int i)
{
	t_double3	values;

	if (i == 1)
	{
		if (ft_strstr(line.data, "Rot") != NULL)
		{
			check_pars_nbr_value(line, 3);
			values = pick_values(line, 3);
			add_value(env, &values, i);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
	if (i == 3 || i == 6)
		test_decoup_balise(line.data, i);
	pars_object_line3(env, line, i);
}

void		pars_object_line(t_env *env, t_buff line, int i)
{
	t_double3	values;

	if (i == 0)
	{
		if (ft_strstr(line.data, "Pos") != NULL)
		{
			check_pars_nbr_value(line, 3);
			values = pick_values(line, 3);
			add_value(env, &values, i);
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
			add_value(env, &values, i);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
	pars_object_line2(env, line, i);
}

void		pars_light_line(t_env *env, t_buff line, int i)
{
	t_double3	values;

	if (i == 0)
	{
		if (ft_strstr(line.data, "Pos") != NULL)
		{
			check_pars_nbr_value(line, 3);
			values = pick_values(line, 3);
			add_light_value(env, &values, i);
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
			add_light_value(env, &values, i);
		}
		else
			ft_error("Error : Wrong Value Name.\n");
	}
}

void		pars_camera_line(t_env *env, t_buff line, int i)
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
