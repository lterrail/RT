/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 19:02:15 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/29 14:43:30 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "libft.h"
# include "get_next_line.h"
# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include "scene.h"

# define MAX_LINE 10000
# define E_SUCCESS 1
# define E_ERROR 0

# define OPEN_RT_FILE_FAILED -10
# define RT_FILE_TOO_BIG -11
# define FAILED_TO_MALLOC -12
# define ERR_TOO_MANY_SCENE -13
# define ERR_TOO_MANY_CAMERA -14
# define ERR_TOO_MANY_OBJECTS -15
# define ERR_TOO_MANY_LIGHTS -16
# define ERR_TOO_MANY_PARAM -17
# define ERR_NO_SCENE -18
# define ERR_NO_CAMERA -19
# define ERR_NO_OBJECTS -20
# define ERR_NO_LIGHTS -21
# define ERR_NO_LIGTH -22
# define ERR_NO_PARAM -23
# define ERR_NO_ELEM -24
# define WRONG_EMBRACE -25
# define ERR_CAMERA -26
# define WRONG_ELEM_NAME -27
# define WRONG_MATERIAL_NAME -28
# define ERR_OBJ -29
# define ERR_PARAM -30
# define ERR_LIGHT -31
# define ERR_FILL_LIGHT -32
# define ERR_FILL_OBJ -33
# define ERR_FILL_PARAM -34
# define OPEN_OBJ_FILE_FAILED -35
# define OBJ_FILE_TOO_BIG -36
# define ERR_MESH -37
# define BAD_IMG_EXTENSION -38
# define BAD_IMG_TYPE -39
# define SEEK_IMG_FAIL -40
# define FREAD_FAIL -41
# define FCLOSE_FAIL -42
# define MLX_ERROR -43
# define ERR_CREATE_THREAD -44

typedef struct		s_err
{
	int				ret;
	char			name[50];
}					t_err;

/*
** init rt parsing
*/
int					parse(char **file, t_scene *scene);

/*
** check the scene
*/
int					check_semicolon(char *line);
int					check_quadric(t_obj *obj);
int					check_obj(char **file, int *line);
int					check_cam(char **file, int *i);
int					check_scene(char **file);
int					check_var(char *line);
int					check_mesh(t_obj *obj, int *id);
int					check_lights(char **file, int *line);
int					check_values(t_obj *obj);
int					check_param(char **file, int *line);

/*
** fill the structures
*/
int					fill_obj_material(char **file, t_obj *obj, int *i);
int					fill_light(char **file, t_scene *scene);
int					fill_mesh_value(char **tab, double v[4], int *pos);
int					fill_obj(char **file, t_scene *scene);
int					fill_param(char **file, t_scene *scene);
void				add_obj(t_obj **head, t_obj *new);

/*
** exit
*/
int					is_valid_fread(FILE *fimg);
void				free_tab(char **tab);
void				ft_usage();

/*
** utils
*/
int					get_type_text(char *line);
int					get_quadric_type(char *q);
double				get_value(char *str);
int					get_vec(double vec[4], char *line);
int					get_color(double color[4], char *line);
double				get_max(double a, double b);
int					is_number(char *str);
int					is_valid_vector(char **split);
int					is_token(char *line, char *token);
int					count_elem(char **file);
int					count_line(char **file);

#endif
