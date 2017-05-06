#include "../rtv1.h"

static t_double3		pixel_ray_init(t_double3 camera_dir, int x, int y)
{
	t_double3	pixel_ray;
	double		aspect_ratio;
	double		scale;

	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	scale = tan((FOV * 0.5 * PI) / 180.0);
	pixel_ray.x = (2 * ((x + 0.5) / (double)WIDTH) - 1) * aspect_ratio * scale;
	pixel_ray.y = (1 - 2 * (y + 0.5) / (double)HEIGHT) * scale;
	pixel_ray.z = -1;
	pixel_ray = normalize(pixel_ray);
	pixel_ray = rotation(pixel_ray, camera_dir, REGULAR_MATRIX);
	return (pixel_ray);
}

static t_double3        pixel_ray_init_aa(t_double3 camera_dir, int x, int y, int i)
{
    t_double3   pixel_ray;
    double      aspect_ratio;
    double      scale;

    aspect_ratio = (double)WIDTH / (double)HEIGHT;
    scale = tan((FOV * 0.5 * PI) / 180.0);
    if (i == 0)
    {
        pixel_ray.x = (2 * ((x + 0.25) / (double)WIDTH) - 1) * aspect_ratio * scale;
        pixel_ray.y = (1 - 2 * (y + 0.25) / (double)HEIGHT) * scale;
    }
    else if (i == 1)
    {
        pixel_ray.x = (2 * ((x + 0.75) / (double)WIDTH) - 1) * aspect_ratio * scale;
        pixel_ray.y = (1 - 2 * (y + 0.25) / (double)HEIGHT) * scale;
    }
    else if (i == 2)
    {
        pixel_ray.x = (2 * ((x + 0.25) / (double)WIDTH) - 1) * aspect_ratio * scale;
        pixel_ray.y = (1 - 2 * (y + 0.75) / (double)HEIGHT) * scale;
    }
    else if (i == 3)
    {
        pixel_ray.x = (2 * ((x + 0.75) / (double)WIDTH) - 1) * aspect_ratio * scale;
        pixel_ray.y = (1 - 2 * (y + 0.75) / (double)HEIGHT) * scale;
    }
    pixel_ray.z = -1;
    pixel_ray = normalize(pixel_ray);
    pixel_ray = rotation(pixel_ray, camera_dir, REGULAR_MATRIX);
    return (pixel_ray);
}

static void            init_de_merde(void *env, int *index)
{
    pthread_mutex_lock(&((t_env*)env)->my_mutex);
    *index = ((t_env*)env)->count;
    pthread_cond_signal(&((t_env*)env)->cond);
    pthread_mutex_unlock(&((t_env*)env)->my_mutex);
}

void            *render(void *env)
{
    t_double3   pixel_ray[4];
    t_double3   color;
    int         x;
    int         y;
    int         index;
    int         i;
 
    init_de_merde(env, &index);
    y = 0;
    while (y < HEIGHT / THREAD)
    {
        x = 0;
        while (x < WIDTH)
        {
             i = 0;
            if (((t_env*)env)->scene->aliaising)
            {
                while(i < 4)
                {
                    pixel_ray[i] = pixel_ray_init_aa(((t_env*)env)->scene->camera.dir, x,
                    y + ((HEIGHT / THREAD) * (index)), i);
                    color = v_plus_v(color, raytracer((t_vector){((t_env*)env)->scene->camera.pos, 
                    pixel_ray[i]}, ((t_env*)env)->scene, NULL, 0));
                    color = scale_v(color, 0.50);
                    i++;
                }
            }
            else
            {
                pixel_ray[0] = pixel_ray_init(((t_env*)env)->scene->camera.dir, x,
                y + ((HEIGHT / THREAD) * (index)));
                color = raytracer((t_vector){((t_env*)env)->scene->camera.pos, 
                pixel_ray[0]}, ((t_env*)env)->scene, NULL, 0);
            }
            if (((t_env*)env)->scene->effect == 1)
                color_sepia((t_env*)env, color, x, y, index);
            else if (((t_env*)env)->scene->effect == 3)
                color_sepia_neg((t_env*)env, color, x, y, index);
            else if (((t_env*)env)->scene->effect == 3)
                color_neg((t_env*)env, color, x, y, index);
            else
                color_standard((t_env*)env, color, x, y, index);
            x++;
        }
        y++;
    }
    pthread_exit(0);
}
