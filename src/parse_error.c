#include "../rtv1.h"

int			pars_error(t_pars *pars, char *message, char *line)
{
	char		*str;
	char		*ligne;
	int			ret;

	str = (char*)malloc(sizeof(char) * ft_strlen(message) + 20);
	ligne = ft_itoa(pars->ligne);
	str = ft_strcpy(str, "Ligne ");
	str = ft_strjoin(str, ligne);
	str = ft_strjoin(str, " : ");
	str = ft_strjoin(str, message);
	if (pars->error == 0)
		ft_putendl(line);
	pars->error++;
	ft_putendl(str);
	if (str != NULL)
		free(str);
	if (ligne != NULL)
		free(ligne);
	if (ft_strcmp(message, "Warning : Some Value aren't specified in <balise>") == 0)
		return (1);
	return (0);
}