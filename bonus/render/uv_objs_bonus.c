/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_objs_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalghamd <jalghamd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 23:26:43 by jalghamd          #+#    #+#             */
/*   Updated: 2026/10/30 23:55:34 by jalghamd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

void	get_sphere_uv(t_hit *hit, double *u, double *v)
{
	t_sphere	*sp;
	t_vec3		d;

	sp = (t_sphere *)hit->obj->data;
	d = normvec(vecsub(hit->point, sp->center));
	*u = 0.5 + (atan2(d.x, -d.z) / (2.0 * M_PI));
	*v = 0.5 + (asin(d.y) / M_PI);
}

void	get_plane_uv(t_hit *hit, double *u, double *v)
{
	t_plane	*pl;
	t_vec3	ref;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	diff;

	pl = (t_plane *)hit->obj->data;
	ref = (t_vec3){0, 1, 0};
	if (fabs(pl->normal.y) > 0.9)
		ref = (t_vec3){0, 0, 1};
	tangent = normvec(veccross(ref, pl->normal));
	bitangent = normvec(veccross(pl->normal, tangent));
	diff = vecsub(hit->point, pl->point);
	*u = dotprod(diff, tangent);
	*v = dotprod(diff, bitangent);
}

void	get_cylinder_uv(t_hit *hit, double *u, double *v)
{
	t_cylinder	*cy;
	t_vec3		diff;
	t_vec3		radial;
	double		h;

	cy = (t_cylinder *)hit->obj->data;
	diff = vecsub(hit->point, cy->center);
	h = dotprod(diff, cy->axis);
	if (fabs(fabs(h) - (cy->height / 2.0)) < EPSILON)
	{
		*u = (diff.x / cy->diameter) + 0.5;
		*v = (diff.z / cy->diameter) + 0.5;
		return ;
	}
	*v = (h + (cy->height / 2.0)) / cy->height;
	radial = normvec(vecsub(diff, vecscale(cy->axis, h)));
	*u = 0.5 + (atan2(radial.z, radial.x) / (2.0 * M_PI));
}

void	get_cone_uv(t_hit *hit, double *u, double *v)
{
	t_cone	*co;
	t_vec3	diff;
	t_vec3	radial;
	double	h;

	co = (t_cone *)hit->obj->data;
	diff = vecsub(hit->point, co->center);
	h = dotprod(diff, co->axis);
	if (fabs(h - co->height) < EPSILON)
	{
		*u = (diff.x / co->diameter) + 0.5;
		*v = (diff.z / co->diameter) + 0.5;
		return ;
	}
	*v = h / co->height;
	radial = normvec(vecsub(diff, vecscale(co->axis, h)));
	*u = 0.5 + (atan2(radial.z, radial.x) / (2.0 * M_PI));
}
