/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 17:26:25 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/12 18:45:21 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		init_grad(t_noise *p)
{
	static int perm[] = { 151, 160, 137, 91, 90, 15, 131, 13, 201, 95,
	96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21,
	10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219,
	203, 117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125,
	136, 171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146,
	158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55,
	46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209,
	76, 132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86,
	164, 100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202,
	38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182,
	189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70, 221,
	153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113,
	224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238,
	210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14, 239, 107, 49,
	192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115, 121, 50, 45,
	127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141,
	128, 195, 78, 66, 215, 61, 156, 180 };

	p->g[0] = perm[p->i + perm[p->j]] % 8;
	p->g[1] = perm[p->i + 1 + perm[p->j]] % 8;
	p->g[2] = perm[p->i + perm[p->j + 1]] % 8;
	p->g[3] = perm[p->i + 1 + perm[p->j + 1]] % 8;
}

static void		init_noise(t_noise *p)
{
	double	unit;

	unit = 1.0 / sqrt(2);
	p->grad[0][0] = unit;
	p->grad[0][1] = unit;
	p->grad[1][0] = -unit;
	p->grad[1][1] = unit;
	p->grad[2][0] = unit;
	p->grad[2][1] = -unit;
	p->grad[3][0] = -unit;
	p->grad[3][1] = -unit;
	p->grad[4][0] = 1;
	p->grad[4][1] = 0;
	p->grad[5][0] = -1;
	p->grad[5][1] = 0;
	p->grad[6][0] = 0;
	p->grad[6][1] = 1;
	p->grad[7][0] = 0;
	p->grad[7][1] = -1;
}

static double	grad_vec(t_noise *p, double x, double y, int type)
{
	double	tmpx;
	double	tmpy;

	tmpx = x - p->x_s;
	tmpy = y - p->y_s;
	p->s = p->grad[p->g[0]][0] * tmpx + p->grad[p->g[0]][1] * tmpy;
	tmpx = x - (p->x_s + 1);
	tmpy = y - p->y_s;
	p->t = p->grad[p->g[1]][0] * tmpx + p->grad[p->g[1]][1] * tmpy;
	tmpx = x - p->x_s;
	tmpy = y - (p->y_s + 1);
	p->u = p->grad[p->g[2]][0] * tmpx + p->grad[p->g[2]][1] * tmpy;
	tmpx = x - (p->x_s + 1);
	tmpy = y - (p->y_s + 1);
	p->v = p->grad[p->g[3]][0] * tmpx + p->grad[p->g[3]][1] * tmpy;
	if (type == PERLIN)
		return (perlin(x, y, p));
	else if (type == WOOD)
		return (wood(x, y, p));
	else
		return (marble(x, y, p));
}

static double	perlin_noise(double x, double y, t_text *tex, t_noise *p)
{
	x /= tex->resolution;
	y /= tex->resolution;
	p->x_s = (int)x;
	p->y_s = (int)y;
	p->i = p->x_s & 255;
	p->j = p->y_s & 255;
	init_grad(p);
	return (grad_vec(p, x, y, tex->e_text));
}

void			perlin_text(t_text *tex, double obj_color[4])
{
	t_noise	p;
	double	x;
	double	y;
	double	n;
	int		pos;

	init_noise(&p);
	pos = 0;
	y = -1;
	while (++y < tex->h)
	{
		x = -1;
		while (++x < tex->w)
		{
			n = perlin_noise(x, y, tex, &p) * 255;
			if (tex->e_text != PERLIN)
				n = (unsigned char)fabs(n) / 255.0;
			else
				n /= 255;
			tex->img[pos++] = n * (obj_color[2] * 255);
			tex->img[pos++] = n * (obj_color[1] * 255);
			tex->img[pos++] = n * (obj_color[0] * 255);
		}
	}
}
