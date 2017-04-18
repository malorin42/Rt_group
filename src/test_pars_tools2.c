#include "../rtv1.h"

void			empty_lign(t_buff line)
{
	ft_parse_space(&line);
	if (line.data[line.i] != '\0')
		ft_error("Error : not an empty line between <Object>.\n");
}
