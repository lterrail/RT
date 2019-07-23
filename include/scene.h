/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 12:24:07 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/29 14:40:14 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "transformation.h"

typedef struct		s_text
{
	enum
	{
		BMP = 1,
		PERLIN = 2,
		WOOD = 3,
		MARBLE = 4,
		SKYBOX = 5
	}				e_text;
	double			resolution;
	char			signature[2];
	unsigned char	offset;
	int				w;
	int				h;
	unsigned char	*img;
	int				i;
	int				j;
	unsigned int	freq;
}					t_text;

typedef struct		s_ray
{
	int				inside;
	double			dir[4];
	double			ori[4];
	t_transform		t;
}					t_ray;

typedef struct		s_mesh
{
	double			v0[4];
	double			v1[4];
	double			v2[4];
}					t_mesh;

typedef struct		s_obj
{
	enum
	{
		QUADRIC = 1,
		MESH = 2,
		TORE = 3,
		CUBE = 4
	}				e_type;
	enum
	{
		ELLIPSOID = 1,
		ELLIPTIC_PARABOLOID = 2,
		HYPERBOLIC_PARABOLOID = 3,
		ELLIPTIC_HYPERBOLOID_ONE = 4,
		ELLIPTIC_HYPERBOLOID_TWO = 5,
		ELLIPTIC_CONE = 6,
		ELLIPTIC_CYLINDER = 7,
		HYPERBOLIC_CYLINDER = 8,
		PARABOLIC_CYLINDER = 9,
		SPHEROID = 10,
		SPHERE = 11,
		PARABOLOID = 12,
		HYPERBOLOID_ONE = 13,
		HYPERBOLOID_TWO = 14,
		CONE = 15,
		CYLINDER = 16,
		PLAN = 17,
	}				e_quadric;
	t_mesh			mesh;
	t_quadric		q;
	t_text			texture;
	double			ambiant;
	double			reflect;
	double			refract;
	double			shine;
	int				transparency;
	double			p_spec;
	double			pos[4];
	double			rayon;
	double			alpha;
	double			r_tore;
	double			albedo;
	double			normal[4];
	double			normal2[4];
	double			point[4];
	double			color[4];
	double			dir[4];
	int				id;
	t_transform		t;
	char			*path;
	struct s_obj	*down;
	struct s_obj	*next;
	pthread_mutex_t	mutex;
}					t_obj;

typedef struct		s_lux
{
	double			color[4];
	double			pos[4];
	double			lux;
	double			normal[4];
	double			inter[4];
	double			dir[4];
	struct s_lux	*next;
	double			direct;
}					t_lux;

typedef	struct		s_cam
{
	t_transform		t;
	double			fov;
	double			pos[4];
	double			dir[4];
}					t_cam;

typedef	struct		s_param
{
	char			*shader;
	double			light;
	double			aliasing;
	double			depth;
}					t_param;

typedef struct		s_scene
{
	t_cam			cam;
	t_lux			*light;
	t_obj			*obj;
	t_param			param;
}					t_scene;

#endif
