/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 19:29:03 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/10/25 06:18:38 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT.h"

t_vec3	get_normal(t_ray ray, t_hit *hit)
{
	t_vec3		n;
	t_cylinder	*cy;
	double		m;

	n = (t_vec3){0, 0, 0};
	if (hit->obj->type == OBJ_SPHERE)
		n = normvec(vecsub(hit->point, ((t_sphere *)hit->obj->data)->center));
	else if (hit->obj->type == OBJ_PLANE)
		n = ((t_plane *)hit->obj->data)->normal;
	else if (hit->obj->type == OBJ_CYLINDER)
	{
		cy = (t_cylinder *)hit->obj->data;
		m = dotprod(vecsub(hit->point, cy->center), cy->axis);
		if (fabs(fabs(m) - cy->height / 2) < EPSILON)
			n = cy->axis;
		else
			n = normvec(vecsub(hit->point, vecadd(cy->center, vecscale(cy->axis,
								m))));
	}
	if (dotprod(ray.dir, n) > 0)
		n = vecscale(n, -1.0);
	return (n);
}

static int	in_shadow(t_hit *hit, t_vec3 n, t_light *light, t_scene *scene)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	double	light_dist;

	shadow_ray.origin = vecadd(hit->point, vecscale(n, EPSILON));
	shadow_ray.dir = normvec(vecsub(light->pos, hit->point));
	light_dist = veclen(vecsub(light->pos, hit->point));
	if (find_closest_hit(shadow_ray, scene, &shadow_hit))
	{
		if (shadow_hit.t < light_dist)
			return (1);
	}
	return (0);
}

static void	apply_light(t_color *light_cont, t_hit *hit, t_light *light,
		t_scene *scene)
{
	t_vec3	l;
	double	intensity;

	l = normvec(vecsub(light->pos, hit->point));
	if (!in_shadow(hit, hit->normal, light, scene))
	{
		intensity = fmax(0, dotprod(l, hit->normal));
		light_cont->r += intensity * light->brightness * 1;
		light_cont->g += intensity * light->brightness * 1;
		light_cont->b += intensity * light->brightness * 1;
	}
}

static void	clamp_light(t_color *light_cont)
{
	if (light_cont->r > 1)
		light_cont->r = 1;
	if (light_cont->g > 1)
		light_cont->g = 1;
	if (light_cont->b > 1)
		light_cont->b = 1;
}

void	check_lights(t_ray ray, t_hit *hit, t_scene *scene)
{
	t_list	*curr;
	t_color	light_cont;

	curr = scene->lights;
	light_cont.r = scene->amb_light.ratio * scene->amb_light.color.r;
	light_cont.g = scene->amb_light.ratio * scene->amb_light.color.g;
	light_cont.b = scene->amb_light.ratio * scene->amb_light.color.b;
	hit->normal = get_normal(ray, hit);
	while (curr)
	{
		apply_light(&light_cont, hit, (t_light *)curr->content, scene);
		curr = curr->next;
	}
	clamp_light(&light_cont);
	hit->color.r *= light_cont.r;
	hit->color.g *= light_cont.g;
	hit->color.b *= light_cont.b;
}
