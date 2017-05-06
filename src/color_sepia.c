#include "../rtv1.h"

void			color_sepia(t_env *env, t_double3 color, int x, int y, int index)
{
	t_color		rgb_color;
	t_color		tmp;
	int 		r;
	int 		g;
	int 		b;

	rgb_color.b.a = 0x00;
	rgb_color.b.r = 255 * color.x;
	rgb_color.b.g = 255 * color.y;
	rgb_color.b.b = 255 * color.z;
	r = (int)(rgb_color.b.r * 0.393) + (rgb_color.b.g * 0.769) + (rgb_color.b.b * 0.189);
	g = (int)(rgb_color.b.r * 0.349) + (rgb_color.b.g * 0.686) + (rgb_color.b.b * 0.168);
	b = (int)(rgb_color.b.r * 0.272) + (rgb_color.b.g * 0.534) + (rgb_color.b.b * 0.131);
	rgb_color.b.r = r;
	rgb_color.b.g = g;
	rgb_color.b.b = b;
	color_pixel_image(rgb_color, (WIDTH * y + x) * env->img[index]->opp, env->img[index]);
}
