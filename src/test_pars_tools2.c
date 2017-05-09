#include "../rtv1.h"

void			empty_lign(t_env *env, t_pars *pars, t_buff line)
{
	ft_parse_space(&line);
	if (line.data[line.i] != '\0')
		pars_error(pars, "Error : not an empty line between <Object>.", line.data);
}
