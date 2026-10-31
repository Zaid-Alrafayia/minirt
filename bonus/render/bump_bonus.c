/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 00:53:00 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/31 21:12:35 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

static double	get_height_sample(t_tex *bump, double u, double v)
{
	int				x;
	int				y;
	unsigned char	*pixel;

	u = u - floor(u);
	v = v - floor(v);
	x = (int)(u * (bump->width - 1));
	y = (int)((1.0 - v) * (bump->height - 1));
	pixel = (unsigned char *)(bump->addr
			+ (y * bump->line_len + x * (bump->bpp / 8)));
	return ((pixel[0] + pixel[1] + pixel[2]) / (3.0 * 255.0));
}

static void	get_tbn_vectors(t_vec3 normal, t_vec3 *tangent, t_vec3 *bitangent)
{
	t_vec3	ref;

	ref = (t_vec3){0, 1, 0};
	if (fabs(normal.y) > 0.9)
		ref = (t_vec3){0, 0, 1};
	*tangent = normvec(veccross(normal, ref));
	*bitangent = normvec(veccross(normal, *tangent));
}

t_vec3	bump_mapping(t_hit *hit, t_tex *bump)
{
	double	uv[2];
	double	d[2];
	t_vec3	t;
	t_vec3	b;
	t_vec3	shift;

	get_object_uv(hit, &uv[0], &uv[1]);
	d[0] = (get_height_sample(bump, uv[0] + (1.0 / bump->width), uv[1])
			- get_height_sample(bump, uv[0] - (1.0 / bump->width), uv[1]));
	d[1] = (get_height_sample(bump, uv[0], uv[1] + (1.0 / bump->height))
			- get_height_sample(bump, uv[0], uv[1] - (1.0 / bump->height)));
	get_tbn_vectors(hit->normal, &t, &b);
	shift = vecadd(vecscale(t, d[0] * 0.7), vecscale(b, d[1] * 0.7));
	return (normvec(vecsub(hit->normal, shift)));
}
