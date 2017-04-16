#include "../rtv1.h"

static t_double3		hex_to_double(char	*str)
{
	char		*tmp;
	t_double3	rgb;
	double		hex[6];
	int			i;

	i = 0;
	while(str[i])
	{
		str[i] = ft_toupper(str[i]);
		if (str[i] >= 48 && str[i] <= 57)
			hex[i] = str[i] - 48;
		else if (str[i] >= 65 && str[i] <= 70)
			hex[i] = str[i] - 55;
		else
			ft_error("Mauvais typage hexadecimal.");
		i++;
	}
	rgb.x = (hex[0] * 16 + hex[1]) / 255;
	rgb.y = (hex[2] * 16 + hex[3]) / 255;
	rgb.z = (hex[4] * 16 + hex[5]) / 255;
	return (rgb);
}

void		check_color_light(t_light **light, char *value)
{
	t_light		*tmp;
	char		*tmp_c;

	tmp_c = ft_strnew(7);
	tmp = *light;
	if (ft_strcmp(value, "red") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, RED));
	else if (ft_strcmp(value, "blue") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, BLUE));
	else if (ft_strcmp(value, "green") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, GREEN));
	else if (ft_strcmp(value, "lightblue") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, LIGHT_BLUE));
	else if (ft_strcmp(value, "lightgreen") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, LIGHT_GREEN));
	else if (ft_strcmp(value, "orange") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, ORANGE));
	else if (ft_strcmp(value, "pink") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, PINK));
	else if (ft_strcmp(value, "purple") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, PURPLE));
	else
		tmp->color = hex_to_double(value);
	free(tmp_c);
}

void		check_color_obj(t_object **object, char *value)
{
	t_object	*tmp;
	char		*tmp_c;

	tmp_c = ft_strnew(7);
	tmp = *object;
	if (ft_strcmp(value, "red") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, RED));
	else if (ft_strcmp(value, "blue") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, BLUE));
	else if (ft_strcmp(value, "green") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, GREEN));
	else if (ft_strcmp(value, "lightblue") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, LIGHT_BLUE));
	else if (ft_strcmp(value, "lightgreen") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, LIGHT_GREEN));
	else if (ft_strcmp(value, "orange") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, ORANGE));
	else if (ft_strcmp(value, "pink") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, PINK));
	else if (ft_strcmp(value, "purple") == 0)
		tmp->color = hex_to_double(ft_strcpy(tmp_c, PURPLE));
	else
		tmp->color = hex_to_double(value);
	free(tmp_c);
}
