/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaalrafa <zaalrafa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 19:29:03 by zaalrafa          #+#    #+#             */
/*   Updated: 2026/10/30 23:52:37 by zaalrafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../miniRT_bonus.h"

t_vec3	get_normal(t_ray ray, t_hit *hit)
{
	t_vec3	n;
	t_cone	*co;
	double	m;

	n = (t_vec3){0, 0, 0};
	if (hit->obj->type == OBJ_SPHERE)
		n = normvec(vecsub(hit->point, ((t_sphere *)hit->obj->data)->center));
	else if (hit->obj->type == OBJ_PLANE)
		n = ((t_plane *)hit->obj->data)->normal;
	else if (hit->obj->type == OBJ_CYLINDER)
		n = get_cylinder_normal(hit, (t_cylinder *)hit->obj->data);
	else if (hit->obj->type == OBJ_CONE)
	{
		co = (t_cone *)hit->obj->data;
		m = dotprod(vecsub(hit->point, co->center), co->axis);
		if (fabs(m - co->height) < EPSILON)
			n = co->axis;
		else
			n = normvec(vecsub(vecsub(hit->point, co->center),
						vecscale(co->axis, m * (1.0 + co->k_sq))));
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

static void	apply_light(t_color *final_c, t_hit *hit, t_light *light, t_ray ray)
{
	t_vec3	l;
	double	diff;
	double	spec;

	l = normvec(vecsub(light->pos, hit->point));
	diff = fmax(0.0, dotprod(l, hit->normal)) * light->brightness;
	spec = 0.0;
	if (diff > 0.0)
		spec = get_specular(l, hit->normal, ray.dir, light->brightness);
	final_c->r += (hit->color.r * diff + spec) * light->color.r;
	final_c->g += (hit->color.g * diff + spec) * light->color.g;
	final_c->b += (hit->color.b * diff + spec) * light->color.b;
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
	t_list *curr;
	t_color final_c;
	t_light *light;

	curr = scene->lights;
	final_c.r = hit->color.r * scene->amb_light.ratio
		* scene->amb_light.color.r;
	final_c.g = hit->color.g * scene->amb_light.ratio
		* scene->amb_light.color.g;
	final_c.b = hit->color.b * scene->amb_light.ratio
		* scene->amb_light.color.b;
	hit->normal = get_normal(ray, hit);
	while (curr)
	{
		light = (t_light *)curr->content;
		if (!in_shadow(hit, hit->normal, light, scene))
			apply_light(&final_c, hit, light, ray);
		curr = curr->next;
	}
	clamp_light(&final_c);
	hit->color = final_c;
}