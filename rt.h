/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malorin <malorin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 17:11:36 by jbahus            #+#    #+#             */
/*   Updated: 2017/05/11 20:52:22 by malorin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# include <dirent.h>

# define WIDTH 1200
# define HEIGHT 800
# define FOV 30
# define DEPTH_MAX 5
# define THREAD 32

# define STRUCTURENOTIFYMASK (1L<<17)
# define DESTROYNOTIFY 17

# define KEY_ESC 53
# define KEY_ENTER 36
# define L_ARROW 123
# define U_ARROW 126
# define R_ARROW 124
# define D_ARROW 125

# define PI 3.14159265

# define SPHERE 0
# define PLANE 1
# define CYLINDER 2
# define CONE 3
# define SPOTLIGHT 4

# define AMBIANT 0.05

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

# define REGULAR_MATRIX	1
# define INVERSE_MATRIX -1

typedef struct			s_double2
{
	double				x;
	double				y;
}						t_double2;

typedef struct			s_double3
{
	double				x;
	double				y;
	double				z;
}						t_double3;

typedef struct			s_vector
{
	t_double3			pos;
	t_double3			dir;
}						t_vector;

typedef struct			s_light
{
	t_double3			pos;
	t_double3			dir;
	t_double3			color;
	t_image				*texture;
	struct s_light		*next;
}						t_light;

typedef struct			s_negobj
{
	t_double3			pos;
	t_double3			rotation;
	double				radius;
	struct s_negobj		*next;
}						t_negobj;

typedef struct			s_object
{
	int					type;
	t_double3			pos;
	t_double3			rotation;
	double				radius;
	t_double3			color;
	double				gloss;
	double				refraction;
	double				reflex;
	double				transparency;
	int					dcp;
	t_double2			dcp_x;
	t_double2			dcp_y;
	t_double2			dcp_z;
	t_double3			text_rot;
	t_image				*texture;
	int					perturbation;
	struct s_object		*next;
}						t_object;

typedef struct			s_surface
{
	t_object			*object;
	double				distance;
	t_double3			point;
	t_double3			normal;
	t_double3			color;
}						t_surface;

typedef struct			s_scene
{
	t_object			*object;
	t_light				*light;
	t_negobj			*negobj;
	t_vector			camera;
	double				ambiant;
	int					effect;
	int					aliaising;
	int					cell_shading;
	int					direct_light;
	int					sepia;
	int					neg;
}						t_scene;

typedef struct			s_pars
{
	int					balise;
	int					ligne;
	int					dcp_text;
	char				**error_mess;
	char				*actual_line;
	int					i_pos;
	int					i_dir;
	int					i_radius;
	int					dcp;
	int					i_dcp;
	int					i_ambiant;
	int					i_aliai;
	int					i_dir_light;
	int					i_sepia;
	int					i_negative;
	int					texture;
	int					error;
}						t_pars;

typedef struct			s_menu
{
	int					menu_lvl;
	int					index;
	int					i_page;
	int					page_max;
	int					nbr_scn;
	char				**tab_scn;
	char				*path;
	int					render;
	t_image				*img;
}						t_menu;

typedef struct			s_header
{
	char				type[2];
	int					reserved;
	int					file_size;
	int					offset;
}						t_header;

typedef struct			s_info
{
	int					header_size;
	int					img_size;
	int					nb_color;
	int					important_color;
	int					compression;
	int					width;
	int					height;
	int					x_res;
	int					y_res;
	short				panes;
	short				bpp;
}						t_info;

typedef struct			s_env
{
	void				*mlx;
	void				*win_scene;
	void				*win_menu;
	t_image				*img[THREAD];
	t_scene				*scene;
	t_menu				*menu;
	t_header			header;
	t_info				h_infos;
	pthread_mutex_t		my_mutex;
	pthread_cond_t		cond;
	int					nbr_obj;
	int					count;
}						t_env;

int						loop_hook(t_env *env);
int						key_hook(int keycode, t_env *env);
int						key_hook(int keycode, t_env *env);
int						red_cross(t_env env);
void					key_enter_menu(t_env *env);

t_double3				pick_values(t_buff line, int nbr);
int						check_pars_nbr_value(t_env *env, t_pars *pars,
							t_buff line, int nbr);
void					empty_lign(t_env *env, t_pars *pars, t_buff line);

t_image					*init_texture(void *mlx, char *file);
void					add_value_neg(t_env *env, t_double3 *values, int i);
void					add_light_value(t_env *env, t_double3 *values, int i);
void					add_double_param(t_buff line, char *type,
							t_object **object, char *value);
void					add_camera_value(t_env *env, t_double3 *values, int i);
int						add_on_off_value(t_object **object, char *value,
							t_pars *pars, t_buff line);
void					add_texture(t_env *env, char *value, t_pars *pars,
							t_buff line);
void					add_value(t_env *env, t_double3 *values, int i);
char					*analyse_balise_lign(t_env *env, t_pars *pars,
							t_buff line, char *type);
void					add_perturbation(t_object **object, char *value,
							t_pars *pars, t_buff line);
int						is_type_xyz(char *type, int i);
void					check_if_balise(t_env *env, t_buff line, t_pars *pars);
void					check_files(int fd, t_env *env);
void					check_neg_obj_name(t_env *env, char *name,
							t_pars *pars);
void					check_sphere_obj(t_env *env, t_buff line, int i);
void					check_cylinder_obj(t_env *env, t_buff line, int i);
void					check_cone_obj(t_env *env, t_buff line, int i);
char					*check_line_type(t_env *env, t_pars *pars, t_buff line);
void					check_light_obj(t_env *env, t_buff line, int i);
void					check_camera_obj(t_env *env, t_buff line, int i);
int						check_object_type(t_env *env, char *type,
							t_pars *pars, t_buff line);
int						is_end_balise(t_env *env, t_pars *pars, t_buff line);
void					check_color_obj(t_buff line, t_pars *pars,
							t_object **object, char *value);
void					check_color_light(t_buff line, t_pars *pars,
							t_light **light, char *value);
void					check_plane_obj(t_env *env, t_buff line, int i);
void					test_decoup_balise(t_env *env,
							t_pars *pars, char *line);
void					pars_in_balise(t_env *env, t_pars *pars, t_buff line);
void					pars_head_balise(t_env *env, t_pars *pars,
							t_buff line);
int						pars_error(t_pars *pars, char *message, char *line);

void					neg_obj_add(t_negobj **first, t_negobj *new);
t_negobj				*neg_obj_new();
void					init_light_obj(t_env *env, t_pars *pars,
							t_light **light, t_buff line);
void					init_object(t_env *env, t_pars *pars, int obj,
							t_object **object);
void					init_neg_obj(t_env *env, t_pars *pars,
							t_negobj **neg_obj);
void					init_scene(t_env *env);
void					object_add(t_object **first, t_object *new);
t_object				*object_new(int type);
void					light_add(t_light **first, t_light *new);
t_light					*light_new(t_env *env, t_pars *pars, t_buff line);

void					swap(double *t0, double *t1);
double					dot_product(t_double3 vec1, t_double3 vec2);
t_double3				cross_product(t_double3 vec1, t_double3 vec2);
t_double3				normalize(t_double3 vec);
t_double3				find_point(t_double3 origin, t_double3 dir,
							double scalar);
t_double3				vec_minus_vec(t_double3 vec1, t_double3 vec2);
t_double3				vec_plus_vec(t_double3 vec1, t_double3 vec2);
t_double3				scale_vec(t_double3 vec, double scalar);
t_double3				v_minus_v(t_double3 vec1, t_double3 vec2);
t_double3				rotation(t_double3 point, t_double3 angles,
							int inverse);
t_double3				scale_v(t_double3 vec, double scalar);
t_double3				v_scale_v(t_double3 vec1, t_double3 vec2);
t_double3				vec_scale_vec(t_double3 vec1, t_double3 vec2);
t_double3				v_plus_v(t_double3 vec1, t_double3 vec2);
t_vector				transform_ray(t_vector ray, t_object *object);
double					length_v(t_double3 vec);
double					max_double(double a, double b);
double					min_double(double a, double b);
double					min_positive(double a, double b);
double					abs_double(double n);
int						solve_quadratic(double a, double b, double c,
							t_double2 *distance);

t_double3				rotation(t_double3 point, t_double3 angles,
							int inverse);

t_double3				color_reflected(t_vector ray, t_scene *scene,
							t_surface *surface, int depth);
t_double3				reflect(t_double3 incidence, t_double3 normal);
t_double3				color_refracted(t_vector ray, t_scene *scene,
							t_surface *surface, int depth);
t_double3				raytracer(t_vector ray, t_scene *scene,
							t_object *to_ignore, int depth);
t_double3				color_mix(t_double3 color1, double ratio,
							t_double3 color2);
t_surface				*intersect(t_vector ray, t_scene *scene,
							t_object *to_ignore);
void					*render(void *env);
t_double3				aa(t_env *env, t_double3 color, int *xy, int *i);
void					color_standard(t_env *env, t_double3 color, int *xy,
							int index);
void					cel_shading(double *dot_light);
void					color_pixel_image(t_color color, int pixel_start,
							t_image *image);
void					get_surface_normal(t_surface *surface);

void					get_nearest_sphere(t_vector ray, t_object *sphere,
							t_surface *surface, t_scene *scene);
void					get_nearest_plane(t_vector ray, t_object *plane,
							t_surface *surface, t_scene *scene);
void					get_nearest_cylinder(t_vector ray, t_object *cylinder,
							t_surface *surface, t_scene *scene);
void					get_nearest_cone(t_vector ray, t_object *cone,
							t_surface *surface, t_scene *scene);

int						intersect_plane(t_vector ray, t_object *plane,
							double *distance);
t_surface				*cut_object(t_vector ray_r, t_object *object,
							t_double2 distance, t_scene *scene);
int						is_between_cuts(t_vector ray_s, double distance,
							t_object *object);
t_double3				get_normal(t_object *object, t_double3 point);

t_image					*ft_new_image(void *mlx, int width, int height,
							int thread);

t_double3				cylindrical_mapping(t_surface *surface, t_vector ray,
							t_object *object);
t_double3				spherical_mapping(t_surface *surface, t_vector ray,
							t_object *object);
t_double3				planar_mapping(t_surface *surface, t_vector ray,
							t_object *object);

/*
** Fonction multi_thread
*/

void					multi_threading(t_env *env);

/*
** Fonction menu
*/

int						wrong_files(char const *str);
int						key_menu(int keycode, t_env *env);
void					init_menu(t_env *env, const char *argv);
void					draw_menu(t_env *env);
void					render_menu(t_env *env);
void					ft_draw_right_arrow(t_env *env);
void					ft_draw_left_arrow(t_env *env);
void					setup_scene_menu(t_env *env);

/*
** Fonction save image
*/

void					save_img(t_env *env);

#endif
