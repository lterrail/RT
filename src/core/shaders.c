/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 14:09:34 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/12 17:46:45 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	cartoon_filter(unsigned char *pixel)
{
	int		i;
	int		max;

	i = -1;
	max = 0;
	while (max <= 255)
	{
		i = -1;
		while (++i < 3)
			if (pixel[i] >= max && pixel[i] < max + 25)
				pixel[i] = max;
		max += 25;
	}
}

static void	negative_filter(unsigned char *pixel)
{
	int		i;

	i = -1;
	while (++i < 3)
		pixel[i] = 255 - pixel[i];
}

static void	sepia_filter(unsigned char *pixel)
{
	double	t[3];

	t[2] = 0.389 * pixel[2] + 0.769 * pixel[1] + 1.189 * pixel[0];
	t[1] = 0.349 * pixel[2] + 0.686 * pixel[1] + 0.168 * pixel[0];
	t[0] = 0.272 * pixel[2] + 0.534 * pixel[1] + 0.131 * pixel[0];
	if (t[2] > 255)
		pixel[2] = 255;
	else
		pixel[2] = (unsigned char)t[2];
	if (t[1] > 255)
		pixel[1] = 255;
	else
		pixel[1] = (unsigned char)t[1];
	if (t[0] > 255)
		pixel[0] = 255;
	else
		pixel[0] = (unsigned char)t[0];
}

static void	grey(unsigned char *pixel)
{
	double a;

	a = (pixel[0] + pixel[1] + pixel[2]) / 3;
	pixel[0] = a;
	pixel[1] = a;
	pixel[2] = a;
}

void		apply_shader(t_image *img, char *shader)
{
	int		x;
	int		y;

	y = -1;
	while (++y < SIZE_H)
	{
		x = -1;
		while (++x < SIZE_W)
		{
			if (!(ft_strncmp(shader, "cartoon", ft_strlen(shader))))
				cartoon_filter(
				(unsigned char *)&img->img[img->size_line * y + x * 4]);
			else if (!(ft_strncmp(shader, "negative", ft_strlen(shader))))
				negative_filter(
				(unsigned char *)&img->img[img->size_line * y + x * 4]);
			else if (!(ft_strncmp(shader, "sepia", ft_strlen(shader))))
				sepia_filter(
				(unsigned char *)&img->img[img->size_line * y + x * 4]);
			else if (!(ft_strncmp(shader, "grey", ft_strlen(shader))))
				grey(
				(unsigned char *)&img->img[img->size_line * y + x * 4]);
			else
				return ;
		}
	}
}
