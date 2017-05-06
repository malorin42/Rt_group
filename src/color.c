#include "../rtv1.h"

void			color_standard(t_env *env, t_double3 color, int x, int y, int index)
{
	t_color		rgb_color;

	rgb_color.b.a = 0x00;
	rgb_color.b.r = 255 * max_double(0, min_double(1, color.x));
	rgb_color.b.g = 255 * max_double(0, min_double(1, color.y));
	rgb_color.b.b = 255 * max_double(0, min_double(1, color.z));
	color_pixel_image(rgb_color, (WIDTH * y + x) * env->img[index]->opp, env->img[index]);
}
