/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 19:26:14 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/27 13:56:31 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H
# include <mlx.h>
# include "parser.h"
# define SIZE_W 1280
# define SIZE_H 720
# define ESCAPE 53

typedef struct		s_image
{
	char			*img;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_image;

typedef struct		s_mlx
{
	void			*p_mlx;
	void			*p_win;
	void			*p_img;
}					t_mlx;

typedef struct		s_all
{
	t_image			img;
	char			**file;
	t_mlx			mlx;
	char			*shader;
	int				i;
	pthread_mutex_t	mutex;
	char			*av;
}					t_all;

int					read_file(char *file_name, t_all *all);
void				free_scene(int error, t_all *all, t_scene *scene);

#endif
