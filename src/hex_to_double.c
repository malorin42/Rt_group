#include "../rtv1.h"

t_double3	hex_to_double(char	*str)
{
	t_double3	rgb;
	int			hex[6];
	int			i;

	i = 0;
	while(str[i])
	{
		if (str[i] >= 31 && str[i] <= 39)
			hex[i] = str[i] - 30;
		else if (str[i] >= 41 && str[i] <= 46)
			hex[i] = str[i] - 31;
		else
			ft_error("Mauvais typage hexadecimal.");
		i++;
	}
	rgb.x = (hex[0] * 16 + hex[1]) / 255;
	rgb.y = (hex[2] * 16 + hex[3]) / 255;
	rgb.y = (hex[4] * 16 + hex[6]) / 255;
	return (rgb);
}