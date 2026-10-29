/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 11:11:53 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/10/29 12:48:52 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

static void	check_cap(t_ray ray, t_cone *co, t_vec3 cap_c, double *best_t)
{
	double	denom;
	double	t;
	t_vec3	p;

	denom = dotprod(ray.dir, co->axis);
	if (fabs(denom) < 0.0001)
		return ;
	t = -dotprod(vecsub(ray.origin, cap_c), co->axis) / denom;
	if (t <= 0.001 || t >= *best_t)
		return ;
	p = vecadd(ray.origin, vecscale(ray.dir, t));
	if (dotprod(vecsub(p, cap_c), vecsub(p, cap_c)) <= pow(co->diameter / 2.0,
			2))
		*best_t = t;
}

static void	check_cone_wall(t_ray ray, t_cone *co, double *best_t)
{
	t_vec3	vec;
	double	abc[3];
	double	disc;
	double	t;
	double	m;

	vec = vecsub(ray.origin, co->center);
	abc[0] = dotprod(ray.dir, ray.dir) - (1.0 + co->k_sq) * pow(dotprod(ray.dir,
				co->axis), 2);
	abc[1] = dotprod(vec, ray.dir) - (1.0 + co->k_sq) * dotprod(vec, co->axis)
		* dotprod(ray.dir, co->axis);
	abc[2] = dotprod(vec, vec) - (1.0 + co->k_sq) * pow(dotprod(vec, co->axis),
			2);
	disc = abc[1] * abc[1] - abc[0] * abc[2];
	if (disc < 0 || fabs(abc[0]) < EPSILON)
		return ;
	t = (-abc[1] - sqrt(disc)) / abc[0];
	m = dotprod(vec, co->axis) + t * dotprod(ray.dir, co->axis);
	if (t > EPSILON && t < *best_t && m >= 0.0 && m <= co->height)
		*best_t = t;
	t = (-abc[1] + sqrt(disc)) / abc[0];
	m = dotprod(vec, co->axis) + t * dotprod(ray.dir, co->axis);
	if (t > EPSILON && t < *best_t && m >= 0.0 && m <= co->height)
		*best_t = t;
}

int	intersect_cone(t_ray ray, t_cone *co, t_hit *hit)
{
	hit->t = DBL_MAX;
	check_cap(ray, co, vecadd(co->center, vecscale(co->axis, co->height)),
		&hit->t);
	check_cone_wall(ray, co, &hit->t);
	return (hit->t < DBL_MAX);
}
