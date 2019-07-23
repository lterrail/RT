/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teddy <teddy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 20:18:08 by teddy             #+#    #+#             */
/*   Updated: 2019/06/29 14:31:20 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			init_skybox(t_obj *s)
{
	s->rayon = 200000;
	s->ambiant = 0.9;
	s->shine = 0;
	s->p_spec = 0;
}

int				init_perlin(t_obj *s)
{
	s->texture.h = 4000;
	s->texture.w = 4000;
	if (!(s->texture.img = (unsigned char *)malloc(sizeof(char)
	* s->texture.h * 3 * s->texture.w)))
		return (FAILED_TO_MALLOC);
	if (s->texture.e_text == PERLIN)
		s->texture.resolution = 120;
	else if (s->texture.e_text == MARBLE)
		s->texture.resolution = 120;
	else if (s->texture.e_text == WOOD)
		s->texture.resolution = 2000;
	perlin_text(&s->texture, s->color);
	return (EXIT_SUCCESS);
}

static int		fill_head(t_text *head, FILE *fimg)
{
	if (fseek(fimg, 10, SEEK_SET) < 0)
		return (SEEK_IMG_FAIL);
	fread(&head->offset, sizeof(int), 1, fimg);
	if (!is_valid_fread(fimg))
		return (FREAD_FAIL);
	if (fseek(fimg, 18, SEEK_SET) < 0)
		return (SEEK_IMG_FAIL);
	fread(&head->w, sizeof(int), 1, fimg);
	if (!is_valid_fread(fimg))
		return (FREAD_FAIL);
	if (fseek(fimg, 22, SEEK_SET) < 0)
		return (SEEK_IMG_FAIL);
	fread(&head->h, sizeof(int), 1, fimg);
	if (!is_valid_fread(fimg))
		return (FREAD_FAIL);
	if (!(head->img = malloc(sizeof(unsigned char) * head->h * 3 * head->w)))
		return (FAILED_TO_MALLOC);
	return (EXIT_SUCCESS);
}

int				load_img(char *image_path, t_text *head)
{
	FILE	*fimg;
	char	mn[2];
	int		ret;

	fimg = 0;
	if (!image_path || !(fimg = fopen(image_path, "r")) || (ft_strcmp(".bmp",
				image_path + ft_strlen(image_path) - 4) != 0))
		return (BAD_IMG_EXTENSION);
	fread(mn, sizeof(char) * 2, 1, fimg);
	if (!is_valid_fread(fimg))
		return (FREAD_FAIL);
	if (mn[0] != 'B' || mn[1] != 'M')
		return (BAD_IMG_TYPE);
	if ((ret = fill_head(head, fimg) < 0))
		return (ret);
	if ((ret = fill_img(head, fimg)) < 0 && !fclose(fimg))
		return (ret);
	if (fclose(fimg))
		return (FCLOSE_FAIL);
	return (EXIT_SUCCESS);
}
