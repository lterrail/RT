/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:49:07 by teddy             #+#    #+#             */
/*   Updated: 2019/06/20 12:10:10 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "rt.h"

int			fill_img(t_text *head, FILE *fimg)
{
	int				i;
	int				j;
	int				k;
	unsigned char	buf[3];

	i = 0;
	if (fseek(fimg, head->offset, SEEK_SET) < 0)
		return (SEEK_IMG_FAIL);
	k = head->w * head->h * 3 - 1;
	while (i++ < head->h)
	{
		j = 0;
		while (j++ < head->w)
		{
			fread(buf, 1, 3, fimg);
			if (!is_valid_fread(fimg))
				return (FREAD_FAIL);
			head->img[k--] = buf[0];
			head->img[k--] = buf[1];
			head->img[k--] = buf[2];
		}
	}
	return (EXIT_SUCCESS);
}

static void	get_color_tex(t_obj *s, int i, int j)
{
	int		k;

	k = -1;
	while (++k < 3 && (s->texture.h - i - 1) * s->texture.w - j * 3 + (2 - k)
		< s->texture.w * s->texture.h * 3
			&& (s->texture.h - i - 1) * s->texture.w - j * 3 + (2 - k) > 0)
		s->color[k] = (double)
			((double)s->texture.img[((s->texture.h - i - 1)
				* s->texture.w - j) * 3 + (2 - k)] / 255.0);
}

static void	sphere_tex(t_obj *s, double n2[4])
{
	double	u;
	double	v;
	int		i;
	int		j;

	u = 0.5 + atan2(n2[2], n2[0]) / M_PI * 0.5;
	v = 0.5 - asin(n2[1]) / M_PI;
	i = clamp(u * s->texture.w, 0, s->texture.w - 1);
	j = clamp(v * s->texture.h, 0, s->texture.h - 1);
	return (get_color_tex(s, i, j));
}

void		get_texture(t_obj *s)
{
	double	n2[4];

	ft_memcpy(n2, s->normal, sizeof(double) * 4);
	normalize(n2);
	if (!s || !s->texture.img)
		return ;
	if (s->e_quadric == SPHERE)
		sphere_tex(s, n2);
}
