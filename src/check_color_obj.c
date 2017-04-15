#include "../rtv1.h"

/*
# define RED "ff0000"
# define BLUE "0000ff"
# define GREEN "00ff00"
# define LIGHT_BLUE "ADD8E6"
# define LIGHT_GREEN "90ee90"
# define ORANGE "ffa500"
# define PINK "ffc0cb"
# define PURPLE "800080"
# define DARK_GREEN "006400"
# define DARK_BLUE "00008b"
# define DARK_RED "8b0000"
*/
t_double3	hex_to_double(char	*str)
{
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

void	check_color_obj(t_env *env, char *value)
{
	if (ft_strcmp(value, "red") == 0)
		env->objects->color = hex_to_double(ft_strcpy(RED));
	else if (ft_strcmp(value, "blue") == 0)
		env->objects->color = hex_to_double(ft_strcpy(BLUE));
	else if (ft_strcmp(value, "green") == 0)
		env->objects->color = hex_to_double(ft_strcpy(GREEN));
	else if (ft_strcmp(value, "lightblue") == 0)
		env->objects->color = hex_to_double(ft_strcpy(LIGHT_BLUE));
	else if (ft_strcmp(value, "lightgreen") == 0)
		env->objects->color = hex_to_double(ft_strcpy(LIGHT_GREEN));
	else if (ft_strcmp(value, "orange") == 0)
		env->objects->color = hex_to_double(ft_strcpy(ORANGE));
	else if (ft_strcmp(value, "pink") == 0)
		env->objects->color = hex_to_double(ft_strcpy(PINK));
	else if (ft_strcmp(value, "purple") == 0)
		env->objects->color = hex_to_double(ft_strcpy(PURPLE));
	else if (ft_strcmp(value, "darkgreen") == 0)
		env->objects->color = hex_to_double(ft_strcpy(DARK_GREEN));
	else if (ft_strcmp(value, "darkblue") == 0)
		env->objects->color = hex_to_double(ft_strcpy(DARK_BLUE));
	else if (ft_strcmp(value, "darkred") == 0)
		env->objects->color = hex_to_double(ft_strcpy(DARK_RED));
	else
		env->objects->color = hex_to_double(value);
}
