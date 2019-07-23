/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcottet <fcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 16:30:31 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/27 13:57:15 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "graphic.h"
# include <pthread.h>
# include <stdio.h>
# include <float.h>
# include <pthread.h>
# define E 0.00000001
# define TWO_PI			6.283185207179586476925286766560
# define TWO_PI_3		2.0943951023931954923084
# define TWO_PI_43		4.1887902047863909846168

typedef struct			s_shadow
{
	t_obj				*hit;
	double				d;
	int					depth;
	double				color[4];
	double				dl2;
}						t_shadow;

typedef struct			s_noise
{
	int					x_s;
	int					y_s;
	int					i;
	int					j;
	int					g[4];
	double				s;
	double				t;
	double				u;
	double				v;
	double				cx;
	double				cy;
	double				grad[8][2];
}						t_noise;

typedef struct			s_tore
{
	double				tmp;
	double				tmp_a;
	double				tmp_b;
	double				tmp_c;
	double				tmp_d;
	double				tmp_e;
	double				tmp_f;
}						t_tore;

typedef	struct			s_polynom
{
	double				a0;
	double				a1;
	double				a2;
	double				a3;
	double				a4;
	double				s1;
	double				s2;
	double				s3;
	double				s4;
	double				aa2;
	double				i;
	double				d;
	double				p;
	double				q;
	double				r;
	double				s;
	double				t;
	double				q1;
	double				q2;
	double				q3;
	double				r2;
	double				s_q;
	double				an;
	double				alpha;
}						t_polynom;

typedef struct			s_data
{
	double				color[4];
	int					depth;
	t_obj				*hit;
	double				d;
	double				point[4];
	double				norm[4];
	double				phong;
	double				ambiant[4];
	double				specular[4];
	double				diffuse[4];
	double				direct[4];
	double				kr;
	double				inter;
	double				ir_prev;
	double				ir_actual;
}						t_data;

typedef struct			s_ref
{
	t_ray				new;
	double				i[4];
	double				n[4];
	double				k;
	double				cosi;
	double				etat;
	double				etai;
	double				eta;
	double				kr;
}						t_ref;

typedef struct			s_bar
{
	int					dl;
	int					dlmax;
	int					max;
	double				ij[2];
}						t_bar;

typedef struct			s_aliasing
{
	double				aa;
	double				sx;
	double				sy;
}						t_aliasing;

/*
** CORE/closest_obj.c
*/
void					closest_obj(t_obj *obj, t_ray r, t_data *data);

/*
** CORE/core.c
*/
void					core(t_all *all);

/*
** CORE/init.var.c
*/
void					set_vec(double vec[4], double x, double y, double z);
void					init_transform(t_transform *t, double *pos,
						double *dir);
void					init_vec(double vec[4]);
t_all					init_var(t_all all);
void					init_data(t_data *data, t_scene *scene);

/*
** CORE/load_obj.c
*/
int						fill_img(t_text *head, FILE *fimg);
int						load_obj(t_obj *obj);

/*
** CORE/perlin_interpolation.c
*/
double					wood(double x, double y, t_noise *p);
double					marble(double x, double y, t_noise *p);
double					perlin(double x, double y, t_noise *p);

/*
** CORE/perlin.c
*/
void					perlin_text(t_text *tex, double color_obj[4]);

/*
** CORE/print_bar.c
*/
void					print_bar(char c, t_bar bar);

/*
** CORE/raytracer.c
*/
void					raytrace(t_scene *scene, t_ray r, t_data *data,
						double depth);

/*
** CORE/shaders.c
*/
void					apply_shader(t_image *img, char *shader);

/*
** CORE/texture.c
*/
void					get_texture(t_obj *s);

/*
** CORE/texture2.c
*/
int						load_img(char *image_path, t_text *bmp);
void					init_skybox(t_obj *s);
int						init_perlin(t_obj *s);

/*
** CORE/loading_bar.c
*/
void					init_bar(t_bar *bar, t_all *all);
void					manage_bar(t_bar bar);

/*
** MATH_TOOL/cal_point.c
*/
void					cal_point(t_ray r, double point[4], double res);

/*
** MATH_TOOL/clamp.c
*/
double					clamp(double a, double min, double max);
void					clamp_color(double color[4], double min, double max);

/*
** MATH_TOOL/closest_inter.c
*/
double					closest_inter(t_polynom p);

/*
** MATH_TOOL/dbl_swap.c
*/
void					double_swap(double *a, double *b);

/*
** MATH_TOOL/init_polynom.c
*/
void					init_polynom(t_polynom *p);

/*
** MATH_TOOL/inter_[OBJECT].c
*/
double					inter_cube(t_ray r, t_obj *s);
double					inter_quadric(t_ray r, t_obj *s, int flag);
double					inter_tore(t_ray ray, t_obj *obj);
double					inter_mesh(t_ray r, t_obj *s);

/*
** MATH_TOOL/op_vector.c
*/
void					add_vec(double a[4], double b[4], double c[4]);
void					double_vec(double a[4], double b, double c[4]);
void					sub_vec(double a[4], double b[4], double c[4]);
void					mult_vec(double a[4], double b[4], double c[4]);
double					square_norm(double a[4]);

/*
** MATH_TOOL/op_vector2.c
*/
double					dot_product(double v[4], double u[4]);
void					crossproduct(double a[4], double b[4], double vec[4]);

/*
** MATH_TOOL/quadric.c
*/
void					normalquadric(double normal[4], double point[4],
						t_quadric q);
void					init_quadric(t_quadric *q);
double					quadric_solver(t_quadric q, t_ray r);

/*
** MATH_TOOL/resolv4.c
*/
void					resolv4(t_polynom *p);

/*
** MATH_TOOL/resolve.c
*/
void					resolv3(t_polynom *p);
void					resolv(t_polynom *p);

/*
** LIGHT/diffuse_color.c
*/
void					add_diff_spec(t_lux *light, t_data *data, double dl2);

/*
** LIGHT/direct_light.c
*/
void					check_direct_light(t_scene *scene);
void					direct_light(t_lux *light, t_data *data, t_ray r);

/*
** LIGHT/get_color.c
*/
void					getcolor(t_scene *scene, t_data *data);

/*
** LIGHT/reflection.c
*/
t_ray					reflection(t_ray r, t_data *data);

/*
** LIGHT/refraction.c
*/
int						refraction(t_ray r, t_data *data, t_ray *new);

/*
** MLX_FUNC/event.c
*/
int						event(int key, t_all *all);

/*
** MLX_FUNC/light_pixel.c
*/
char					*light_pixel(int x, int y, t_image *img,
						double color[4]);

void					quit_all(t_all *all);
#endif
