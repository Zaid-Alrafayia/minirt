/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 23:14:04 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/10/19 01:33:35 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

int	intersect_sphere(t_ray ray, t_sphere *sphere, t_hit *hit)
{
	double	t1;
	double	lambda;
	double	t2;
	double	t;
	t_vec3	a;

	a = vecsub(ray.origin, sphere->center);
	lambda = (dotprod(a, ray.dir) * dotprod(a, ray.dir)) - dotprod(ray.dir,
			ray.dir) * (dotprod(a, a) - (sphere->diameter / 2)
			* (sphere->diameter / 2));
	if (lambda < 0.0f)
		return (0);
	t1 = (-dotprod(a, ray.dir) - sqrt(lambda)) / dotprod(ray.dir, ray.dir);
	t2 = (-dotprod(a, ray.dir) + sqrt(lambda)) / dotprod(ray.dir, ray.dir);
	t = t1;
	if (t <= EPSILON)
		t = t2;
	if (t <= EPSILON)
		return (0);
	hit->t = t;
	return (1);
}

int	intersect_plane(t_ray ray, t_plane *plane, t_hit *hit)
{
	double	t;
	double	dom;
	t_vec3	a;

	a = vecsub(ray.origin, plane->point);
	dom = dotprod(ray.dir, plane->normal);
	if (fabs(dom) == 0)
		return (0);
	t = -dotprod(a, plane->normal) / dom;
	if (t > 0.001f)
	{
		hit->t = t;
		return (1);
	}
	return (0);
}

static void	check_cap(t_ray ray, t_cylinder *cy, t_vec3 cap_c, double *best_t)
{
	double	denom;
	double	t;
	t_vec3	p;

	denom = dotprod(ray.dir, cy->axis);
	if (fabs(denom) < 0.0001)
		return ;
	t = -dotprod(vecsub(ray.origin, cap_c), cy->axis) / denom;
	if (t <= 0.001 || t >= *best_t)
		return ;
	p = vecadd(ray.origin, vecscale(ray.dir, t));
	if (dotprod(vecsub(p, cap_c), vecsub(p, cap_c)) <= pow(cy->diameter / 2.0,
			2))
		*best_t = t;
}

static void	check_side(t_ray ray, t_cylinder *cy, t_hit *hit)
{
	t_vec3	vec;
	double	a;
	double	half_b;
	double	lambda;
	double	t;

	vec = vecsub(ray.origin, cy->center);
	a = dotprod(ray.dir, ray.dir) - pow(dotprod(ray.dir, cy->axis), 2);
	half_b = dotprod(vec, ray.dir) - (dotprod(vec, cy->axis) * dotprod(ray.dir,
				cy->axis));
	lambda = (half_b * half_b) - a * (dotprod(vec, vec) - pow(dotprod(vec,
					cy->axis), 2) - pow(cy->diameter / 2.0, 2));
	if (lambda >= 0.0 && fabs(a) >= 0.0001)
	{
		t = (-half_b - sqrt(lambda)) / a;
		if (t > 0.001 && t < hit->t && fabs(dotprod(vec, cy->axis) + t
				* dotprod(ray.dir, cy->axis)) <= cy->height / 2.0)
			hit->t = t;
		t = (-half_b + sqrt(lambda)) / a;
		if (t > 0.001 && t < hit->t && fabs(dotprod(vec, cy->axis) + t
				* dotprod(ray.dir, cy->axis)) <= cy->height / 2.0)
			hit->t = t;
	}
}

int	intersect_cylinder(t_ray ray, t_cylinder *cy, t_hit *hit)
{
	hit->t = DBL_MAX;
	check_cap(ray, cy, vecadd(cy->center, vecscale(cy->axis, cy->height / 2.0)),
		&hit->t);
	check_cap(ray, cy, vecadd(cy->center, vecscale(cy->axis, -cy->height
				/ 2.0)), &hit->t);
	check_side(ray, cy, hit);
	return (hit->t < DBL_MAX);
}
